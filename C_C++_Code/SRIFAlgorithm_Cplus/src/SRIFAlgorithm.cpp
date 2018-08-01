//============================================================================
// Name        : SRIFAlgorithm.cpp
// Author      : xiaogongwei
// Version     :
// Copyright   : Copyright attributed to David
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "SRIFAlgorithm.h"


SRIFAlgorithm::SRIFAlgorithm() {
	// TODO Auto-generated constructor stub
	initVar();

}

SRIFAlgorithm::~SRIFAlgorithm() {
	// TODO Auto-generated destructor stub
}

void SRIFAlgorithm::initVar()
{
	this->m_initSRIF = false;

}
// init prior matrix and transition matrix
void SRIFAlgorithm::InitSRIF(MatrixXd &Rp, MatrixXd &Zp, MatrixXd &Phi, MatrixXd &G, MatrixXd &Rwk_1)
{
	this->m_Rp = Rp;
	this->m_Zp = Zp;
	this->m_Phi = Phi;
	this->m_Phi_Inv = Phi.inverse();
	this->m_G = G;
	this->m_Rwk_1 = Rwk_1;
	this->m_initSRIF = true;
}

/*
*	A  Measurement partials, an M by N matrix.
*	L  Observation Data vector, of length M
*	*/
VectorXd SRIFAlgorithm::SRIFilter(MatrixXd &A, MatrixXd &L)
{
	VectorXd Y;
	if(!m_initSRIF)
	{
		int Acols = A.cols();
		this->m_Rp = MatrixXd::Zero(Acols, Acols);
		this->m_Zp = MatrixXd::Zero(Acols, 1);
		this->m_Phi = MatrixXd::Zero(Acols, Acols);
		this->m_Phi_Inv = MatrixXd::Zero(Acols, Acols);
		this->m_G = MatrixXd::Zero(Acols, Acols);
		this->m_Rwk_1 = MatrixXd::Zero(Acols, Acols);
		this->m_initSRIF = true;
		cout << "Waring: you should use SRIFAlgorithm::InitSRIF init Matrix!" << endl;
	}
	// use SRIF filter and update filter parameter (Rp, Zp)
	SRIFTimeUpdate(this->m_Rp, this->m_Zp, this->m_Phi_Inv, this->m_G, &(this->m_Rwk_1));
	SRIFMeasureUpdate(this->m_Rp, this->m_Zp, A, L);
	// solve Rp*X = Zp
	Y.resize(this->m_Zp.rows());
	gaussBackGen(this->m_Rp, this->m_Zp, Y);
	return Y;
}


/*
 * illustration: use SRIF Factorization Matrix update Time
 * example:
 * |
 * | Rp Zp | QR -> | Rd Zd |
 * | A  L  |       | 0  ed |
 *[Rd Zd; 0 ed] stored in AL. AL as input,meanwhile as output
 *
 * Input:
 * 		Rp: 	a priori square root information (SRI) matrix (an n * n upper triangular matrix)
 * 		Zp: 	a priori SRIF state vector, of length n*1 (state is X, Z = R*X).
 * 		Phi:    transition matrix, an n * n matrix.
 *  	G :     The n by ns matrix associated with process noise.
 *  			The process noise covariance is G*Q*transpose(G) where inverse(Q)
 *  			is transpose(Rw)*Rw. G is destroyed on output.
 *  	Rwk_1:  a priori square root information matrix for the process noise, an ns by ns upper triangular matrix
 * 		Zw :    a priori 'state' associated with the process noise, a vector with ns elements.  Usually set to zero by
 *				the calling routine (for unbiased process noise).
 * 		Rw:     An ns by n matrix which is set to zero by this routine, but is used for output.
 * output:
 * 		Rp: 	updated matrix (upper triangular, dimension N*N)
 * 		Zp: 	updated vector (length N)
 * 		Rwk_1:  a posteriori square root information matrix for the process noise, an ns by ns upper triangular matrix
 * 		Rwx:
 * 		Zw :
 * 		[Rwk_1 Rwx Zw] use to SRIF smoothing data
 * 	where Rp*x = Zp
 * reference: Bierman, G.J. "Factorization Methods for Discrete Sequential
 * 				Estimation," Academic Press, 1977.
 */

void SRIFAlgorithm::SRIFTimeUpdate(MatrixXd &Rp, MatrixXd &Zp, MatrixXd &Phi_Inv, MatrixXd &G,
		MatrixXd *Rwk_1,  MatrixXd *Rwx, MatrixXd *Zw)
{
	int allM = Rwk_1->rows() + Rp.rows(), allN = Rwk_1->cols() + Phi_Inv.cols() + 1;
	MatrixXd allMat, tempRes, tempPhiInv, Rmat;
	allMat.resize(allM, allN);
	// copy Rwk_1 to allMat top left corner
	allMat.block( 0, 0, Rwk_1->rows(), Rwk_1->cols()) = *Rwk_1;
	// compute tempRes = Rp*PhiInv
	tempRes = Rp*Phi_Inv;
	// copy tempRes to allMat bottom center corner
	allMat.block(Rwk_1->rows(), G.cols(), tempRes.rows(), tempRes.cols()) =
			tempRes;
	// compute -Rp*PhiInv*G, store in tempPhiInv = -Rwk_1*PhiInv*G
	tempPhiInv = -tempRes*G;
	// copy tempPhiInv to allMat bottom left corner
	allMat.block(Rwk_1->rows(), 0, tempPhiInv.rows(), tempPhiInv.cols()) = tempPhiInv;
	// copy Zp to allMat
	allMat.block(Rwk_1->rows(), allN - 1, Zp.rows(), 1) = Zp;
	// QR factorization
	QRDecompose(allMat, Rmat);
	// copy data to Rp, Zp
	this->m_Zp = Rmat.block(Rwk_1->rows(), allN - 1, Zp.rows(), 1);
	this->m_Rp = Rmat.block(Rwk_1->rows(), Rwk_1->cols(), Rp.rows(), Rp.cols());
	//save as data, use to smoothing
	if(NULL != Rwx && NULL != Zw)
	{
		// copy allMat top left corner to Rwk_1
		*Rwk_1 = allMat.block(0, 0, Rwk_1->rows(), Rwk_1->cols());
		// copy allMat top left corner to Rwk
		*Rwx = allMat.block(0, Rwk_1->cols(), Rwk_1->rows(), Phi_Inv.cols());
		// copy allMat top left corner to Zw
		*Zw = allMat.block(0, allN - 1, Zw->rows(), 1);
	}
}

/*
 * illustration: use SRIF Factorization Matrix solve Least squre
 * example:
 * | Rp Zp | QR -> | Rd Zd |
 * | A  L  |       | 0  ed |
 *[Rd Zd; 0 ed] stored in A L. A L as input,meanwhile as output
 *
 * Input:
 * 	Rp  a priori SRI matrix (upper triangular, dimension N*N)
 * 	Zp  a priori SRI data vector (length N)
 *	A  Measurement partials, an M by N matrix.
 *	L  Data vector, of length M
 * output:
 * 	Rp: updated matrix (upper triangular, dimension N*N)
 * 	Zp: updated vector (length N)
 * 	where Rp*x = Zp
 * reference: Bierman, G.J. "Factorization Methods for Discrete Sequential
 * 				Estimation," Academic Press, 1977.
 */
void SRIFAlgorithm::SRIFMeasureUpdate(MatrixXd &Rp, MatrixXd &Zp, MatrixXd &A, MatrixXd &L)
{
	int allM =  Rp.rows() + A.rows(), allN = A.cols() + L.cols();
	MatrixXd allMat, Rmat;
	if( Rp.cols() + 1 != allN)
	{
		cout << "ERROR: SRIFAlgorithm::SRIFMeasureUpdate!" << endl;
		exit(1);
	}
//	malloc allM*allN matrix store [Rp Zp;A L]
	allMat.resize(allM, allN);
//	storage Rp, Zp, AL in allMat
	allMat.block(0, 0, Rp.rows(), Rp.cols()) = Rp;
	allMat.block(0, Rp.cols(), Rp.rows(), 1) = Zp;
	allMat.block(Rp.rows(), 0, A.rows(), A.cols()) = A;
	allMat.block(Rp.rows(), allN - 1, L.rows(), L.cols()) = L;
//	QR factorization
	QRDecompose(allMat, Rmat);
//	update Rp, Zp
	this->m_Zp = Rmat.block(0, Rp.cols(), Rp.rows(), 1);
	this->m_Rp = Rmat.block(0, 0, Rp.rows(), Rp.cols());

}



// QR Factorization (Eigen function)
void SRIFAlgorithm::QRDecompose(MatrixXd &eigenMat, MatrixXd &R)
{
	HouseholderQR<MatrixXd> qr;
	qr.compute(eigenMat);
	R = qr.matrixQR().triangularView<Upper>();

	MatrixXd Q1, R1;
	Q1 = eigenMat.colPivHouseholderQr().matrixQ();
	R1 = eigenMat.colPivHouseholderQr().matrixR().triangularView<Upper>();
	cout << "eigenMat" << endl;
	cout << eigenMat << endl;

	cout << "Q1*R1" << endl;
	cout << Q1*R1 << endl;


}

// Gauss factorization back generation
void SRIFAlgorithm::gaussBackGen(MatrixXd &upTri, MatrixXd &L, VectorXd &Y)
{
	int n = L.rows();
	if(Y.size() != L.rows())
	{
		cout << "Waring: SRIFAlgorithm::gaussBackGen." << endl;
		Y.resize(L.rows());
	}
	for(int k = n - 1;k >= 0;k--)
	{
		double sum = 0.0;
		for(int j = k + 1; j < n;j++)
			sum += upTri(k,j)*Y(j);
		Y(k) = (L(k) - sum) / upTri(k, k);
	}
}

