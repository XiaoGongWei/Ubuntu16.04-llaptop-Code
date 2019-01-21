/*
 * MyDefine.h
 *
 *  Created on: May 10, 2018
 *      Author: david
 */

#ifndef MYDEFINE_H_
#define MYDEFINE_H_


//	include some libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mkl.h>
#include <omp.h>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;


//	defining variable
#define  MYDOUBLE double
#define  MYINT int
#define MYEPS 1e-20

// defining struct
typedef struct _matrix{
	MYDOUBLE **mat;
	MYINT m,n;
} MYMatrix;

#define TRACE(string) printf(string)






#endif /* MYDEFINE_H_ */
