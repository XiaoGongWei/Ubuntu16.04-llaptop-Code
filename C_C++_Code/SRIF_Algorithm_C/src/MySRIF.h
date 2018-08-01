/*
 * MySRIF.h
 *
 *  Created on: May 10, 2018
 *      Author: david
 */

#ifndef MYSRIF_H_
#define MYSRIF_H_

//	include some libraries
#include "MyDefine.h"
#include "MyQRDecompose.h"


#ifdef __cplusplus
extern "C" {
#endif

// The most primitive use SRIF Factorization Matrix solve Least squre
// function ID : 1
void SRIFMeasureUpdate(MYMatrix *Rp, MYMatrix *Zp, MYMatrix *AL);
void SRIFMeasureUpdateA(MYMatrix *allMat);

// use SRIF Factorization Matrix update Time
// function ID : 2
void SRIFTimeUpdate(MYMatrix *Rp, MYMatrix *Zp, MYMatrix *Phi, MYMatrix *G,
		MYMatrix *Rwk_1,  MYMatrix *Rwx, MYMatrix *Zw);

// Compute Cholesky decomposition of symmetric positive definite matrix using Crout algorithm.
// function ID : 3
void lowerCholesky(MYMatrix *A, MYMatrix *L);

int matrixInv(MYMatrix *matrix);





#ifdef __cplusplus
}
#endif


#endif /* MYSRIF_H_ */
