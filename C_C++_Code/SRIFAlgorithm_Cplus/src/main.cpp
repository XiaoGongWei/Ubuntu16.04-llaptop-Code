#include <iostream>
#include "SRIFAlgorithm.h"
#include "MyMatrix.h"
#include <time.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;




void testSRIF();
void testEigen();
void testSolver();
void testSRIFMax();

void testcloPivQr()
{
	Matrix4d A;
	A << 2,-1,-1,1,
		 1,1,-2,1,
		 4,-6,2,-2,
		 3,6,-9,7;
	Vector4d B(2,4,4,9);
	Vector4d x = A.colPivHouseholderQr().solve(B);
	Vector4d x1 = A.householderQr().solve(B);
	Vector4d x2 = A.llt().solve(B);
	Vector4d x3 = A.ldlt().solve(B);
	std::cout << "The solution is:\n"
			<< x <<"\n\n"
			<< x1 <<"\n\n"
			<<x2<<"\n\n"
			<<x3 <<std::endl;
	MatrixXd Q1, R1, E1;
	Q1 = A.colPivHouseholderQr().matrixQ();
	R1 = A.colPivHouseholderQr().matrixR().triangularView<Upper>();
	cout << "Q1 * R1" << "\n" << Q1 * R1 << "\n";



}


int main() {

	MatrixXd csvMat;
	MyMatrix matrix;
//	testcloPivQr();
//	csvMat = matrix.readCSV("/home/david/Documents/eclipse-workspace1/SRIFAlgorithm/src/N.csv");
//	matrix.printMatrix(csvMat);
//	matrix.writeCSV("/home/david/Documents/eclipse-workspace1/SRIFAlgorithm/src/xiao.csv", csvMat);
//	testSolver();
	testSRIFMax();
//	testSRIF();
//	testEigen();
	return 0;
}

void testSRIFMax()
{
		SRIFAlgorithm srifAlg;
		MatrixXd Rp, Zp, A, L, Phi, G, Phi_Inv, Rwk_1, RAL;
		VectorXd Y;
		clock_t time_start = 0, time_end = 0;
		cout << "test big data." << endl;
//		init update time data
		Rwk_1 = MatrixXd::Random(3000, 3000);
		Rp = MatrixXd::Random(3000, 3000);
		Zp = MatrixXd::Random(3000, 1);
		Phi = MatrixXd::Random(3000, 3000);
		Phi_Inv = MatrixXd::Random(3000, 3000);
		G = MatrixXd::Random(3000, 3000);

//		init measure data
		A = MatrixXd::Random(3000, 3000);
		L = MatrixXd::Random(3000, 1);


//		use SRIF filter
		srifAlg.InitSRIF(Rp, Zp, Phi, G, Rwk_1);

		time_start = clock();
		Y = srifAlg.SRIFilter(A, L);
		time_end = clock();
		cout << "SRIF filter Elapsed time is "
			<< (double)(time_end - time_start)/CLOCKS_PER_SEC<< "seconds." << endl;
//		cout << "*****Y*****" << endl;
//		cout << Y << endl;
//		cout << "*****A*Y - L*****" << endl;
//		cout << A*Y - L << endl;
}



void testSolver()
{
	//线性方程求解 Ax =B;
	Matrix4d A;
	A << 2,-1,-1,1,
	     1,1,-2,1,
	     4,-6,2,-2,
	     3,6,-9,7;
	Vector4d L(2+0.01, 4+0.08, 4+0.2, 9+0.6);
//	Vector4d x1 = A.colPivHouseholderQr().solve(L);
//	Vector4d x2 = A.fullPivHouseholderQr().solve(L);
//	Vector4d x3 = A.householderQr().solve(L);
//	Vector4d x4 = A.llt().solve(L);
//	Vector4d x5 = A.ldlt().solve(L);
//	cout << "The solution is:\n" << x1 <<"\n\n"<<x2<<"\n\n"<<x3 <<"\n\n"<< x4 << "\n\n"<< x5 <<endl;

	MatrixXd csvMat, Nmat, Lmat;
	MyMatrix matrix;
	int selectCol = 0;
	csvMat = matrix.readCSV("/home/david/Documents/eclipse-workspace1/SRIFAlgorithm/src/N.csv");
	selectCol = csvMat.cols() - 1;
	Lmat = csvMat.col(selectCol);
	Nmat = csvMat.leftCols(selectCol);
	cout.precision(10);
	cout << Nmat << endl;
	cout << Lmat << endl;
	cout << "Yd = inv(Nmat)*Lmat" << endl;
	cout << Nmat.inverse()*Lmat << endl;
//	solver as colPivHouseholderQr
	cout << "***colPivHouseholderQr***" << endl;
	cout << Nmat.colPivHouseholderQr().solve(Lmat) << endl;
//	matrix.printMatrix(Lmat);


}

void testSRIF()
{
		SRIFAlgorithm srifAlg;
		MatrixXd Rp, Zp, A, L, Phi, G, Phi_Inv, Rwk_1, RAL, tempR, AL;
		VectorXd Y;
//		init data
		Rp.resize(3, 3);
		Zp.resize(3, 1);
		A.resize(4, 3);
		L.resize(4, 1);
		Phi.resize(3, 3);
		Phi_Inv.resize(3, 3);
		G.resize(3, 3);
		Rwk_1.resize(3, 3);
		// prior Matrix Rp*x = Zp
		Rp << 3, 0, 0,
			0, 100, 0,
			0, 0, 100;
		Zp << 3.8,
			110.5,
			116.3;
		A<<12, 11, 2,
			13, 14, 15,
			11, 22, 12,
			16, 14, 21;
		L << 30.3,
			45.5,
			51.2,
			55.3;
		AL.resize(4, 4);
		AL <<12, 11, 2, 30.3,
			13, 14, 15, 45.5,
			11, 22, 12, 51.5,
			16, 14, 21, 55.3;
		srifAlg.QRDecompose(AL, tempR);
		// state transition Matrix Xk = Phi*Xk_1 + G*wk
		Phi << 1, 0, 0,
			0, 1, 0,
			0, 0, 1;
		Phi_Inv = Phi.inverse();
		G << 0, 0, 0,
			0, 1, 0,
			0, 0, 0;
		// noise of state transition Rwk_1 and smoothing data [Rwk_1 Rwx Zw]
		Rwk_1 << 1, 0, 0,
			0, 1, 0,
			0, 0, 0;
//		use SRIF filter
		srifAlg.InitSRIF(Rp, Zp, Phi, G, Rwk_1);
		int i = 0;
		while(i < 1000)
		{
			Y = srifAlg.SRIFilter(A, L);
			cout << i << ": *****Y******" << endl;
			cout << Y << endl;
			i++;
		}
}

void testEigen()
{
	//线性方程求解 Ax =B;
	Matrix4d A;
	A << 2,-1,-1,1,
		 1,1,-2,1,
		 4,-6,2,-2,
		 3,6,-9,7;
	Vector4d B(2,4,4,9);
	Vector4d x = A.colPivHouseholderQr().solve(B);
	Vector4d x2 = A.llt().solve(B);
	Vector4d x3 = A.ldlt().solve(B);
	std::cout << "The solution is:\n" << x <<"\n\n"<<x2<<"\n\n"<<x3 <<std::endl;

}
