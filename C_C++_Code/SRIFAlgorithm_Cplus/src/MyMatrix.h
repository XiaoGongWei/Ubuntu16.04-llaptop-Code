/*
 * MyMatrix.h
 *
 *  Created on: May 21, 2018
 *      Author: david
 */

#ifndef MYMATRIX_H_
#define MYMATRIX_H_
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class MyMatrix {
public:
	MyMatrix();
	virtual ~MyMatrix();
	MatrixXd readCSV(const char *filename);
	bool writeCSV(const char *filename, const MatrixXd &mat);
	void printMatrix(const MatrixXd &mat);

};


#endif /* MYMATRIX_H_ */
