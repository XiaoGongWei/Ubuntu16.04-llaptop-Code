/*
 * SRIFAlgorithm.h
 *
 *  Created on: May 13, 2018
 *      Author: david
 */

#ifndef SRIFALGORITHM_H_
#define SRIFALGORITHM_H_
#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;


class SRIFAlgorithm {
public:
	SRIFAlgorithm();
	virtual ~SRIFAlgorithm();
	// init prior matrix and transition matrix
	void InitSRIF(MatrixXd &Rp, MatrixXd &Zp, MatrixXd &Phi, MatrixXd &G, MatrixXd &Rwk_1);
	// only input observation to SRIF Filter
	VectorXd SRIFilter(MatrixXd &A, MatrixXd &L);
	//set transition matrix
	void setPhi(MatrixXd &newPhi) { this->m_Phi = newPhi; this->m_Phi_Inv = newPhi.inverse();}
	//set inverse of transition matrix
	void setPhi_Inv(MatrixXd &newPhiInv) { this->m_Phi_Inv = newPhiInv; }
	void setRwk_1(MatrixXd &newRwk_1) { this->m_Rwk_1 = newRwk_1; }
	void setG(MatrixXd &newG) { this->m_G = newG; }
	void getQ(MatrixXd &Q){ Q =  (this->m_Rp.transpose()*this->m_Rp).inverse();}
	// QR Factorization (Eigen)
	void QRDecompose(MatrixXd &eigenMat, MatrixXd &R);

private:
	// initVar
	void initVar();
	// The most primitive use SRIF Factorization Matrix solve Least squre
	void SRIFMeasureUpdate(MatrixXd &Rp, MatrixXd &Zp, MatrixXd &A, MatrixXd &L);
	// use SRIF Factorization Matrix update Time
	void SRIFTimeUpdate(MatrixXd &Rp, MatrixXd &Zp, MatrixXd &Phi_Inv, MatrixXd &G,
			MatrixXd *Rwk_1 = NULL,  MatrixXd *Rwx = NULL, MatrixXd *Zw = NULL);

	// Gauss factorization back generation
	void gaussBackGen(MatrixXd &upTri, MatrixXd &L, VectorXd &Y);

// Variable
private:
	MatrixXd m_Rp, m_Zp, m_Phi, m_Phi_Inv,
			 m_G, m_Rwk_1, m_Q;
	bool m_initSRIF;
};

#endif /* SRIFALGORITHM_H_ */
