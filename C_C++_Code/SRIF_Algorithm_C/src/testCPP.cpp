//============================================================================
// Name        : testCPP.cpp
// Author      : xiaogongwei
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "MySRIF.h"





void timeTest()
{
	MYMatrix aa,bb;
	clock_t time_start = 0, time_end = 0;
	MYINT mat_size[2] = {0};

	printf("timeTest() Begining.\n");
	mat_size[0] = 3000;mat_size[1] = 1000;
	mallocMatrix(&aa, mat_size[0], mat_size[1]);
	mallocMatrix(&bb, mat_size[0], mat_size[1]);
	for(int i = 0;i < mat_size[0];i++)
		for(int j = 0;j < mat_size[1];j++)
		{
			aa.mat[i][j] = i+j;
			bb.mat[i][j] = i+j;
		}

//	time_start = clock();
//	QRDecompose(&aa);
//	time_end = clock();
//	printf("QRDecompose Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);

	time_start = clock();
	QRDecomposeA(&bb);
	time_end = clock();
	printf("QRDecomposeA Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);

	time_start = clock();
	QREigenFun(&bb);
	time_end = clock();
	printf("QREigenFun Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);


	// test QR Eigen direct
	HouseholderQR<MatrixXd> qr;
	MatrixXd eigenMat, R;
	eigenMat.resize(mat_size[0], mat_size[1]);
	for(int i = 0;i < mat_size[0];i++)
		for(int j = 0;j < mat_size[1];j++)
			eigenMat(i,j) = 1;


	time_start = clock();
	qr.compute(eigenMat);
	time_end = clock();
	R = qr.matrixQR().triangularView<Upper>();
	printf("QR Eigen Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);


	freeMatrix(&aa);
	freeMatrix(&bb);

}

void SRIFTest()
{
	MYMatrix Rp, L, Zp, AL, Phi, G, Rwk_1, Rwx, Zw;
	mallocMatrix(&Rp, 3, 3);
	mallocMatrix(&Zp, 3, 1);
	mallocMatrix(&Phi, 3, 3);
	mallocMatrix(&G, 3, 3);
	mallocMatrix(&Rwk_1, 3, 3);
	mallocMatrix(&AL, 4, 4);
	// prior Matrix Rp*x = Zp
	Rp.mat[0][0] = 3; Rp.mat[0][1] = 0  ; Rp.mat[0][2] = 0  ;
	Rp.mat[1][0] = 0; Rp.mat[1][1] = 100; Rp.mat[1][2] = 0  ;
	Rp.mat[2][0] = 0; Rp.mat[2][1] = 0  ; Rp.mat[2][2] = 100;
	Zp.mat[0][0] = 3.8  ;
	Zp.mat[1][0] = 110.5;
	Zp.mat[2][0] = 116.3;
	// state transition Matrix Xk = Phi*Xk_1 + G*wk
	Phi.mat[0][0] = 1; Phi.mat[0][1] = 0; Phi.mat[0][2] = 0;
	Phi.mat[1][0] = 0; Phi.mat[1][1] = 1; Phi.mat[1][2] = 0;
	Phi.mat[2][0] = 0; Phi.mat[2][1] = 0; Phi.mat[2][2] = 1;
	G.mat[0][0] = 0; G.mat[0][1] = 0; G.mat[0][2] = 0;
	G.mat[1][0] = 0; G.mat[1][1] = 1; G.mat[1][2] = 0;
	G.mat[2][0] = 0; G.mat[2][1] = 0; G.mat[2][2] = 0;
	// noise of state transition Rwk_1 and smoothing data [Rwk_1 Rwx Zw]
	Rwk_1.mat[0][0] = 1; Rwk_1.mat[0][1] = 0; Rwk_1.mat[0][2] = 0;
	Rwk_1.mat[1][0] = 0; Rwk_1.mat[1][1] = 1; Rwk_1.mat[1][2] = 0;
	Rwk_1.mat[2][0] = 0; Rwk_1.mat[2][1] = 0; Rwk_1.mat[2][2] = 1;
	// Time Update
	printf("\n*****Before Time Update: Rp and Zp******\n");
	printMatrix(&Rp);
	printMatrix(&Zp);
	SRIFTimeUpdate(&Rp, &Zp, &Phi, &G,&Rwk_1, NULL, NULL);
	printf("\n*****end Time Update: Rp and Zp******\n");
	printMatrix(&Rp);
	printMatrix(&Zp);
	// observe data AL = [A L], where A*x = L
	AL.mat[0][0] = 12; AL.mat[0][1] = 11; AL.mat[0][2] = 2 ; AL.mat[0][3] = 30.3;
	AL.mat[1][0] = 13; AL.mat[1][1] = 14; AL.mat[1][2] = 15; AL.mat[1][3] = 45.5;
	AL.mat[2][0] = 11; AL.mat[2][1] = 22; AL.mat[2][2] = 12; AL.mat[2][3] = 51.2;
	AL.mat[3][0] = 16; AL.mat[3][1] = 14; AL.mat[3][2] = 21; AL.mat[3][3] = 55.3;
	// measure update
	SRIFMeasureUpdate(&Rp, &Zp, &AL);
	printf("\n*****End measure update: Rp and Zp******\n");
	printMatrix(&Rp);
	printMatrix(&Zp);

	freeMatrix(&Rp);
	freeMatrix(&Zp);
	freeMatrix(&Phi);
	freeMatrix(&G);
	freeMatrix(&Rwk_1);
	freeMatrix(&AL);

	printf("\n*****AL******\n");
	printMatrix(&AL);
	printf("\n*****Zp******\n");
	printMatrix(&Zp);
}

void mianTest()
{

		MYMatrix aa, bb, cc,dd;
		MYINT mat_size[3] = {3,2,1};
		clock_t time_start = 0, time_end = 0;
		MYMatrix Rp, Zp, AL, L;

		mallocMatrix(&bb, 5, 3);
		bb.mat[0][0] = 12; bb.mat[0][1] = 11; bb.mat[0][2] = 2;
		bb.mat[1][0] = 13; bb.mat[1][1] = 14; bb.mat[1][2] = 15;
		bb.mat[2][0] = 11; bb.mat[2][1] = 22; bb.mat[2][2] = 12;
		bb.mat[3][0] = 55; bb.mat[3][1] = 121; bb.mat[3][2] = 19;
		bb.mat[4][0] = 14; bb.mat[4][1] = 34; bb.mat[4][2] = 56;
		printf("\n*************\n");
		printMatrix(&bb);
		printf("\n*************\n");
		QRDecomposeA(&bb);
		printf("\n*************\n");
		printMatrix(&bb);
		printf("\n*************\n");
		freeMatrix(&bb);

		//test SRIFMeasureUpdate

		mallocMatrix(&Rp, 3, 3);
		mallocMatrix(&L, 3, 3);
		mallocMatrix(&Zp, 3, 1);
		mallocMatrix(&AL, 4, 4);
		Rp.mat[0][0] = 3; Rp.mat[0][1] = 0  ; Rp.mat[0][2] = 0  ;
		Rp.mat[1][0] = 0; Rp.mat[1][1] = 100; Rp.mat[1][2] = 0  ;
		Rp.mat[2][0] = 0; Rp.mat[2][1] = 0  ; Rp.mat[2][2] = 100;

		lowerCholesky(&Rp, &L);

		printf("\n*****L******\n");
		printMatrix(&L);

		Zp.mat[0][0] = 3.8  ;
		Zp.mat[1][0] = 110.5;
		Zp.mat[2][0] = 116.3;

		AL.mat[0][0] = 12; AL.mat[0][1] = 11; AL.mat[0][2] = 2 ; AL.mat[0][3] = 30.3;
		AL.mat[1][0] = 13; AL.mat[1][1] = 14; AL.mat[1][2] = 15; AL.mat[1][3] = 45.5;
		AL.mat[2][0] = 11; AL.mat[2][1] = 22; AL.mat[2][2] = 12; AL.mat[2][3] = 51.2;
		AL.mat[3][0] = 16; AL.mat[3][1] = 14; AL.mat[3][2] = 21; AL.mat[3][3] = 55.3;

		printf("\n*****AL******\n");
	//	QRDecomposeA(&AL);
		printMatrix(&AL);

//		SRIFMeasureUpdateA(&AL);
		QREigenFun(&AL);
		printf("\n*****AL******\n");
		printMatrix(&AL);
		printf("\n*****Zp******\n");
		printMatrix(&Zp);

		printf("\n*****aa pointer******\n");
		aa.mat = AL.mat;
		aa.m = 2;
		aa.n = 2;
	//	matrixInv(&aa);
		printMatrix(&aa);
		printf("\n*****cc pointer******\n");
		cc.mat = &AL.mat[2];
		cc.m = 2;
		cc.n = 2;
		printMatrix(&cc);


		freeMatrix(&Rp);
		freeMatrix(&Zp);
		freeMatrix(&AL);


	//	mat_size[0] = 3000;mat_size[1] = 1000;
	//	mallocMatrix(&aa, mat_size[0], mat_size[1]);
	//	for(int i = 0;i < mat_size[0];i++)
	//		for(int j = 0;j < mat_size[1];j++)
	//			aa.mat[i][j] = 1;
	//	time_start = clock();
	//	QRDecompose(&aa);
	//	time_end = clock();
	//	printf("QRDecompose Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);
	//
	//	time_start = clock();
	//	QRDecomposeA(&aa);
	//	time_end = clock();
	//	printf("QRDecomposeA Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);
	//
	//	freeMatrix(&aa);

}

void testOpenMP()
{
	double *a, *b, *c;
	double alpha=1, beta=1;
	int SIZE = 5;
	int m=SIZE, n=SIZE, k=SIZE, lda=SIZE, ldb=SIZE, ldc=SIZE, i=0, j=0;
	char transa='n', transb='n';

	a = (double*)malloc(sizeof(double)*SIZE*SIZE);
	b = (double*)malloc(sizeof(double)*SIZE*SIZE);
	c = (double*)malloc(sizeof(double)*SIZE*SIZE);

//	omp_set_num_threads(4);
//	mkl_set_num_threads(1);
	#pragma omp parallel for
	for(int i = 0;i < 11;i++)
	{
		printf("Thread id : %d\n", i);
//		Test(i);
	}
	for( i=0; i<SIZE; i++){
	for( j=0; j<SIZE; j++){
	a[i*SIZE+j]= (double)(i+j);
	b[i*SIZE+j]= (double)(i*j);
	c[i*SIZE+j]= (double)0;
	}
	}
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
	m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
	printf("row\ta\tc\n");
	for ( i=0;i<10;i++){
	printf("%d:\t%f\t%f\n", i, a[i*SIZE], c[i*SIZE]);
	}
	omp_set_num_threads(1);
	#pragma omp parallel for
	for( i=0; i<SIZE; i++){
	for( j=0; j<SIZE; j++){
	a[i*SIZE+j]= (double)(i+j);
	b[i*SIZE+j]= (double)(i*j);
	c[i*SIZE+j]= (double)0;
	printf("j=%d, ",j);
	}
	printf("\n");
	}
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
	m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
	printf("row\ta\tc\n");
	for ( i=0;i<10;i++){
	printf("%d:\t%f\t%f\n", i, a[i*SIZE], c[i*SIZE]);
	}
	omp_set_num_threads(4);
	#pragma omp parallel for
	for( i=0; i<SIZE; i++){
	for( j=0; j<SIZE; j++){
	a[i*SIZE+j]= (double)(i+j);
	b[i*SIZE+j]= (double)(i*j);
	c[i*SIZE+j]= (double)0;
	printf("j=%d, ",j);
	}
	printf("\n");
	}
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
	m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
	printf("row\ta\tc\n");
	for ( i=0;i<10;i++){
	printf("%d:\t%f\t%f\n", i, a[i*SIZE],
	c[i*SIZE]);
	}
	free (a);
	free (b);
	free (c);
	return ;
}


void testCopenMP()
{
	#pragma omp parallel for
	for(int i = 0;i < 11;i++)
	{
		printf("Thread id : %d\n", i);
//		Test(i);
	}
	// test for MKL multiple
	double *A, *B;
	int m = 5, n = 5, k = 2;
	A = (double *)mkl_malloc(m * n * sizeof(double), 64);
	B = (double *)mkl_malloc(n * k * sizeof(double), 64);
	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++)
			A[i*n + j] = 1;
	for(int i = 0;i < n;i++)
			for(int j = 0;j < k;j++)
				B[i*k + j] = 1;

	printf("sizeof:A[0]=%d\n", sizeof(A[0]));
	printf("xiaogongwei\n");
}

int main()
{
	MatrixXd mat;
	cout << mat.rows() << endl;
	mat.resize(5, 5);
	cout << mat.rows() << endl;
	for(int i = 0; i < mat.rows();i++)
		for(int j = 0; j < mat.cols();j++)
			mat(i,j) = 1;
//	mat.setZero(2, 2);
	cout << mat << endl;

//	mianTest();
//	testCopenMP();
//	testOpenMP();
	timeTest();


//
//	testHouseholder();
//	test();

	return 0;
}
