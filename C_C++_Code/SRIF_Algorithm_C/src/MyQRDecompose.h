/*
 * MySRIF.h
 *
 *  Created on: May 5, 2018
 *      Author: david
 */

#ifndef MYQRDECOMPOSE_H_
#define MYQRDECOMPOSE_H_
#include "MyDefine.h"


//	judge if use c++ file include this C file

#ifdef __cplusplus
extern "C" {
#endif




//	test for function
void test();


// The most primitive Householder method
// function ID : 1
void Householder(MYDOUBLE *input_data, MYINT data_len,MYDOUBLE *v, MYDOUBLE *beta);
void HouseholderMatrix(MYMatrix *input_data, MYINT data_len, MYMatrix *v, MYDOUBLE *beta);


// Get the maximum value of the vector
// function ID : 2
MYDOUBLE getAbsMax(MYDOUBLE *input_data, MYINT data_len,MYINT *max_index);

// test for testHouseholder function
// function ID : 3
void testHouseholder();

//use QR Factorization Matrix
// function ID : 4
void QRDecompose(MYMatrix *input_Matrix);
void QRDecomposeA(MYMatrix *input_Matrix);
void QREigenFun(MYMatrix *input_Matrix);

//Get the multiplication value of the two vector
// function ID : 5
MYDOUBLE getVectorDot(MYDOUBLE *vct_a,MYDOUBLE *vct_b, MYINT vct_len);

//Get identity matrix
// function ID : 6
void getIdentityMat(MYMatrix *matrix, MYINT *mat_size);

//Get two matrix products
// function ID : 7
void getMatMultMat(MYMatrix *input_mat1, MYMatrix *input_mat2, MYINT *matmult_size, MYMatrix *output_mat, MYDOUBLE beta);


//Matrix subtraction
// function ID : 8
void getSubMat(MYMatrix *matrix1, MYMatrix *matrix2, MYINT *mat_size, MYMatrix *output_matrix);

//Matrix subtraction
// function ID : 9
void getDotMultMatrix(MYMatrix *matrix, MYDOUBLE beta, MYMatrix *output_matrix, MYINT *mat_size);

//Get matrix Transposition products other matrix
// function ID : 10
void getMatTranMat(MYMatrix *input_mat1, MYMatrix *input_mat2, MYINT *matmult_size, MYMatrix *output_mat);


// illustration: Get the maximum value of the vector size:n*1
// function ID : 11
MYDOUBLE getAbsMax(MYDOUBLE *input_data, MYINT data_len,MYINT *max_index);
MYDOUBLE getAbsMatrixMax(MYMatrix *input_data, MYINT data_len,MYINT *max_index);
MYDOUBLE getAbsMatrixMaxA(MYMatrix *input_data, MYINT data_len,MYINT *max_index);






void mallocMatrix(MYMatrix *matrix, MYINT m, MYINT n);

void freeMatrix(MYMatrix *matrix);

void copyMatrix(const MYMatrix *matrix1, MYMatrix *matrix2);

void printMatrix(MYMatrix *matrix);

#ifdef __cplusplus
}
#endif

#endif /* MYQRDECOMPOSE_H_ */
