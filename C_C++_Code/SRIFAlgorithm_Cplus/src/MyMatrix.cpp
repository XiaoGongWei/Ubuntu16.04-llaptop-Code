/*
 * MyMatrix.cpp
 *
 *  Created on: May 21, 2018
 *      Author: david
 */

#include "MyMatrix.h"

MyMatrix::MyMatrix() {
	// TODO Auto-generated constructor stub

}

MyMatrix::~MyMatrix() {
	// TODO Auto-generated destructor stub
}

void MyMatrix::printMatrix(const MatrixXd &mat)
{
	for(int i = 0;i < mat.rows(); i++)
	{
		for(int j = 0;j < mat.cols();j++)
		{
			cout << mat(i,j) << ", ";
		}
		cout << endl;
	}

}



MatrixXd MyMatrix::readCSV(const char *filename) {

	ifstream in;
	string line;
	in.open(filename, std::ios::in);

	int row = 0;
	int col = 0;

	MatrixXd res(1,1);
	RowVectorXd rowVector(1);

	if (in.is_open()) {

		while (std::getline(in, line)) {

			char *ptr = (char *)line.c_str();
			int len = line.length();

			col = 0;

			char *start = ptr;
			for (int i = 0; i < len; i++) {

				if (ptr[i] == ',') {
					//res(row, col++) = atof(start);
					rowVector(col++) = atof(start);
					start = ptr + i + 1;
					rowVector.conservativeResize(col + 1);
				}
			}
			//res(row++, col) = atof(start);
			rowVector(col) = atof(start);
			res.conservativeResize(row + 1, col + 1);
			res.row(row++) = rowVector;
		}
		in.close();
	}
	return res;
}

bool MyMatrix::writeCSV(const char *filename, const MatrixXd &mat)
{
	ofstream out;
	string line;
	out.open(filename, std::ios::out);
	for(int i = 0; i < mat.rows(); i++)
	{
		for(int j = 0; j < mat.cols();j++)
		{
			out << setprecision(10) << mat(i,j);
			if(j != mat.cols() - 1)
				out << ",";
		}
		out << endl;
	}
	out.close();

	return true;

}

