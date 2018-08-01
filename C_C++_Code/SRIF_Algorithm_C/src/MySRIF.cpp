/*
 * MySRIF.c
 *
 *  Created on: May 10, 2018
 *      Author: david
 */

#include "MySRIF.h"


/*
 * illustration: use SRIF Factorization Matrix solve Least squre
 * example:
 * | Rp Zp | QR -> | Rd Zd |
 * | A  L  |       | 0  ed |
 *[Rd Zd; 0 ed] stored in AL. AL as input,meanwhile as output
 *
 * Input:
 * 	Rp  a priori SRI matrix (upper triangular, dimension N*N)
 * 	Zp  a priori SRI data vector (length N)
 * 	AL concatentation of A and L : AL = [A L], where
 *	A  Measurement partials, an M by N matrix.
 *	L  Data vector, of length M
 * output:
 * 	Rp: updated matrix (upper triangular, dimension N*N)
 * 	Zp: updated vector (length N)
 * 	where Rp*x = Zp
 * reference: Bierman, G.J. "Factorization Methods for Discrete Sequential
 * 				Estimation," Academic Press, 1977.
 */
void SRIFMeasureUpdate(MYMatrix *Rp, MYMatrix *Zp, MYMatrix *AL)
{
	MYINT allM = Rp->m + AL->m, allN = AL->n;
	MYMatrix allMat;
	if( Rp->n + 1 != AL->n)
		TRACE("SRIFMeasureUpdate\n");
//	malloc allM*allN matrix store [Rp Zp;AL]
	mallocMatrix(&allMat, allM, allN);
//	storage Rp, Zp, AL in allMat
	for(int i = 0; i < Rp->m;i++)
	{
		allMat.mat[i][allN - 1] = Zp->mat[i][0];
		for(int j = 0; j < Rp->n;j++)
				allMat.mat[i][j] = Rp->mat[i][j];
	}
	for(int i = 0; i < AL->m;i++)
	{
		allMat.mat[Rp->m + i][allN - 1] = AL->mat[i][allN - 1];
		for(int j = 0; j < AL->n;j++)
				allMat.mat[Rp->m + i][j] = AL->mat[i][j];
	}

	QRDecomposeA(&allMat);
//	update Rp, Zp
	for(int i = 0; i < Rp->m;i++)
	{
		Zp->mat[i][0] = allMat.mat[i][allN - 1];
		for(int j = 0; j < Rp->n;j++)
			Rp->mat[i][j] = allMat.mat[i][j];
	}
	freeMatrix(&allMat);
}


/*
 * illustration: use SRIF Factorization Matrix solve Least squre
 * example:
 * allMat = [Rp Zp; A L]
 * | Rp Zp | QR -> | Rd Zd |
 * | A  L  |       | 0  ed |
 * [Rd Zd; 0 ed] stored in allMat. allMat as input,meanwhile as output
 * where Rd*x = Zd
 * Input:
 * allMat: [Rp Zp; A L]
 * where
 * 	Rp  a priori SRI matrix (upper triangular, dimension N*N)
 * 	Zp  a priori SRI data vector (length N)
 *	A  Measurement partials, an M by N matrix.
 *	L  Data vector, of length M
 * output:
 *  allMat: [Rd Zd;0 ed]
 * 	where Rd*x = Zd
 * reference: Bierman, G.J. "Factorization Methods for Discrete Sequential
 * 				Estimation," Academic Press, 1977.
 */

void SRIFMeasureUpdateA(MYMatrix *allMat)
{
	QRDecomposeA(allMat);
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

void SRIFTimeUpdate(MYMatrix *Rp, MYMatrix *Zp, MYMatrix *Phi, MYMatrix *G,
		MYMatrix *Rwk_1,  MYMatrix *Rwx, MYMatrix *Zw)
{
	MYINT allM = Rwk_1->m + Rp->m, allN = Rwk_1->n + Phi->n + 1;
	MYMatrix allMat, tempPhiInv, tempRes;
	if(Rp->n != Phi->m || Phi->n != G->m || Phi->n != Zp->m || Phi->m != Phi->n)
	{
		TRACE("SRIFTimeUpdate ERROE!\n");
		return ;
	}
	mallocMatrix(&allMat, allM, allN);
	mallocMatrix(&tempPhiInv, Phi->m, Phi->n);
	mallocMatrix(&tempRes, Rp->m, Phi->n);
	// copy Rwk_1 to allMat top left corner
	for(int i = 0;i < Rwk_1->m;i++)
		for(int j = 0;j < Rwk_1->n;j++)
			allMat.mat[i][j] = Rwk_1->mat[i][j];

	// compute tempRes = Rp*inv(PhiInv)
	copyMatrix(Phi, &tempPhiInv);
	matrixInv(&tempPhiInv);
	getMatMultMat(Rp, &tempPhiInv, NULL, &tempRes, 1.0);
	// copy tempRes to allMat bottom center corner
	for(int i = 0;i < tempRes.m;i++)
		for(int j = 0;j < tempRes.n;j++)
			allMat.mat[i + Rwk_1->m][j + G->n] = tempRes.mat[i][j];
	// compute -Rwk_1*inv(PhiInv)*G, store in tempPhiInv = -Rwk_1*inv(PhiInv)*G
	getMatMultMat(&tempRes, G, NULL, &tempPhiInv, -1.0);
	// copy tempPhiInv to allMat bottom left corner
	for(int i = 0;i < tempPhiInv.m;i++)
		for(int j = 0;j < tempPhiInv.n;j++)
			allMat.mat[i + Rwk_1->m][j] = tempPhiInv.mat[i][j];
	// copy Zp to allMat
	for(int i = 0;i < Zp->m;i++)
		allMat.mat[i +  Rwk_1->m][allN - 1] = Zp->mat[i][0];

	// QR Factorization allMat
	QRDecomposeA(&allMat);
	// copy data to Rp, Zp
	for(int i = 0;i < Rp->m;i++)
	{
		Zp->mat[i][0] = allMat.mat[i +  Rwk_1->m][allN - 1];
		for(int j = 0;j < Rp->n;j++)
			Rp->mat[i][j] = allMat.mat[i + Rwk_1->m][j + G->n];
	}


	// copy data to Rwk_1 Rwx Zw
	if(NULL != Rwx && NULL != Zw)
	{
		// copy Rwk_1 to allMat top left corner
		for(int i = 0;i < Rwk_1->m;i++)
			for(int j = 0;j < Rwk_1->n;j++)
				Rwk_1->mat[i][j] = allMat.mat[i][j];
		// copy Rwk_1 to allMat top left corner
		for(int i = 0;i < Rwx->m;i++)
			for(int j = 0;j < Rwx->n;j++)
				Rwx->mat[i][j] = allMat.mat[i][Rwk_1->n + j];
		// copy Rwk_1 to allMat top left corner
		for(int i = 0;i < Zw->m;i++)
				Zw->mat[i][0] = allMat.mat[i][allN - 1];

	}

	freeMatrix(&allMat);
	freeMatrix(&tempPhiInv);
	freeMatrix(&tempRes);

}









//---------------------------------------------------------------------------------
//* reference:  GPSTK soft
	// Compute Cholesky decomposition of symmetric positive definite matrix using Crout
	// algorithm. A = L*L^T where A and L are (nxn) and L is lower triangular reads:
	// [ A00 A01 A02 ... A0n ] = [ L00  0   0  0 ...  0 ][ L00 L10 L20 ... L0n ]
	// [ A10 A11 A12 ... A1n ] = [ L10 L11  0  0 ...  0 ][  0  L11 L21 ... L1n ]
	// [ A20 A21 A22 ... A2n ] = [ L20 L21 L22 0 ...  0 ][  0   0  L22 ... L2n ]
	//           ...                      ...                  ...
	// [ An0 An1 An2 ... Ann ] = [ Ln0 Ln1 Ln2 0 ... Lnn][  0   0   0  ... Lnn ]
	//   but multiplying out gives
	//          A              = [ L00^2
	//                           [ L00*L10  L11^2+L10^2
	//                           [ L00*L20  L11*L21+L10*L20 L22^2+L21^2+L20^2
	//                                 ...
	//    Aii = Lii^2 + sum(k=0,i-1) Lik^2
	//    Aij = Lij*Ljj + sum(k=0,j-1) Lik*Ljk
	// These can be inverted by looping over columns, and filling L from diagonal down.

	/// Compute lower triangular square root of a symmetric positive definite matrix
	/// (Cholesky decomposition) Crout algorithm.
	/// @param A Matrix to be decomposed; symmetric and positive definite, unchanged
	/// @return Matrix lower triangular square root of input matrix
	/// @throw MatrixException if input Matrix is not square
	/// @throw MatrixException if input Matrix is not positive definite
	//---------------------------------------------------------------------------------

void lowerCholesky(MYMatrix *A, MYMatrix *L)
{
	if( (A->m != A->n) || (A->m == 0) )
	{
		TRACE("lowerCholesky Error: Invalid input dimensions...\n");
		exit(1);
	}
	const unsigned int n	= A->n;
	unsigned int i,j,k;

	for(j=0; j<n; j++)	// loop over cols
	{
		double		d		= A->mat[j][j];
		for(k=0; k<j; k++)
			d -= L->mat[j][k]*L->mat[j][k];
		if(d <= 0.0)
		{
			TRACE("lowerCholesky Error: Non-positive eigenvalue...\n");
			exit(1);
		}

		L->mat[j][j] = sqrt(d);
		for(i=j+1; i<n; i++)	// loop over rows below diagonal
		{
			d = A->mat[i][j];
			for(k=0; k<j; k++)
				d -= L->mat[i][k]*L->mat[i][k];
			L->mat[i][j] = d/L->mat[j][j];
		}
	}//end for(j=0; j<n; j++)

}


/*
 * illustration: Finding the inverse of a matrix
 * example:

 *
 * Input:

 * output:


 * reference:
 *
 */

int matrixInv(MYMatrix *matrix)
{
    MYINT i,j,k, n = matrix->n;
    MYINT *is = (int *)malloc(n * sizeof(int)), *js = (int *)malloc(n * sizeof(int));
    MYDOUBLE d,p;
    MYDOUBLE **a = matrix->mat;

    for ( k = 0; k < n; k++)
    {
        d = 0.0;
        for (i=k; i<=n-1; i++)
            for (j=k; j<=n-1; j++)
            {
                p=fabs(a[i][j]);
                if (p>d) { d=p; is[k]=i; js[k]=j;}
            }
            if ( 0.0 == d )
            {
                free(is); free(js); printf("err**not inv\n");
                return(0);
            }
            if (is[k]!=k)
                for (j=0; j<=n-1; j++)
                {
                    p=a[k][j];
                    a[k][j]=a[is[k]][j];
                    a[is[k]][j]=p;
                }
            if (js[k]!=k)
                for (i=0; i<=n-1; i++)
                {
                    p=a[i][k];
                    a[i][k]=a[i][js[k]];
                    a[i][js[k]]=p;
                }
            a[k][k] = 1.0/a[k][k];
            for (j=0; j<=n-1; j++)
                if (j!=k)
                {
                    a[k][j] *= a[k][k];
                }
            for (i=0; i<=n-1; i++)
                if (i!=k)
                    for (j=0; j<=n-1; j++)
                        if (j!=k)
                        {
                            a[i][j] -= a[i][k]*a[k][j];
                        }
            for (i=0; i<=n-1; i++)
                if (i!=k)
                {
                    a[i][k] = -a[i][k]*a[k][k];
                }
    }
    for ( k = n-1; k >= 0; k--)
    {
        if (js[k]!=k)
            for (j=0; j<=n-1; j++)
            {
                p = a[k][j];
                a[k][j] = a[js[k]][j];
                a[js[k]][j]=p;
            }
            if (is[k]!=k)
                for (i=0; i<=n-1; i++)
                {
                    p = a[i][k];
                    a[i][k]=a[i][is[k]];
                    a[i][is[k]] = p;
                }
    }
   free(is);
   free(js);
   return 1;
}


