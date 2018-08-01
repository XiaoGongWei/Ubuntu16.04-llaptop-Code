#include "MyQRDecompose.h"


// test for testHouseholder function
// function ID : 1
void testHouseholder()
{
	int data_len = 15000;
	clock_t time_start = 0, time_end = 0;
	double *x = NULL, y = 0, *v, beta = 0, beta_mat = 0, beta_mat1 = 0;
	MYMatrix x_mat, v_mat, x_mat1, v_mat1;
	mallocMatrix(&x_mat, data_len, 1);
	mallocMatrix(&v_mat, data_len, 1);
	mallocMatrix(&x_mat1, 1, data_len);
	mallocMatrix(&v_mat1, 1, data_len);
	x = (double *)malloc(data_len * sizeof(double));
	v = (double *)malloc(data_len * sizeof(double));
	for(int i = 0; i < data_len;i++)
	{
		x[i] = 5.5;
		x_mat.mat[i][0] = 5.5;
		x_mat1.mat[0][i] = 5.5;
		v[i] = 0;
		v_mat.mat[i][0] = 0;
		v_mat1.mat[0][i] = 0;
	}

	time_start = clock();
	Householder(x, data_len,v, &beta);
	time_end = clock();
	printf("Householder vector Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);

	time_start = clock();
	HouseholderMatrix(&x_mat, data_len, &v_mat, &beta_mat);
	time_end = clock();
	printf("HouseholderMatrix size:n*1 Matrix:Elapsed time is %lf seconds.\n",(double)(time_end - time_start)/CLOCKS_PER_SEC);


	freeMatrix(&x_mat);
	freeMatrix(&v_mat);
	freeMatrix(&x_mat1);
	freeMatrix(&v_mat1);
//	for(int i = 0; i < data_len; i++)
//	{
//		printf("v[%d]=[%lf]\n", i, v[i]);
//	}
//	printf("beta=%lf\n", beta);
}


/*
 * illustration: use QR Factorization Matrix
 * A = Q*[R;0]
 * Q: Orthogonal matrix
 * R: Upper triangulation matrix
 * B = H*A = A - v*w'
 * w = beta*A'*v
 * example:
 * 		A = [1 0 0; 1 0 2.35; 1 3.35 0];
 * 		Q = [-0.58 -0.41 -0.71; -0.58 -0.41 0.71;-0.58 0.82 -1.55e-16]
 * 		R = [-1.73 -1.93 -1.36; 0 2.74 -0.96; 0 0 1.67]
 * Input:
 * 		input_Matrix:size m*n target matrix (double):the Q and R store in input_Matrix
 *      Matrix_size: size 1*2 (double):store Row and column of matrix [m*n]
 * output:
 *
 * reference: 数值线性代数（徐树芳）P95
 */
void QRDecompose(MYMatrix *input_Matrix)
{
	MYINT m = input_Matrix->m, n = input_Matrix->n, flag = 0;
	MYINT input_len = 0, matmult_size[3] = {0}, mat_size[2] = {0},scan_col = n;
	MYMatrix input_data, mat_v, v_wt, A_v_wt, temp_mat1, At_v, W_b_At_v,Wt_b_At_v;
	MYDOUBLE output_data = 0.0, beta = 0.0;
	// m mast great than n
	if (m < n) return ;
	// malloc memory one time
	mallocMatrix(&input_data, m, 1);
	mallocMatrix(&mat_v, m, 1);
	mallocMatrix(&W_b_At_v, n, 1);
	mallocMatrix(&Wt_b_At_v, 1, n);
	mallocMatrix(&At_v, n, 1);
	mallocMatrix(&v_wt, m, n);
	mallocMatrix(&A_v_wt, m, n);
	mallocMatrix(&temp_mat1, m, n);

	if(m == n) scan_col = n - 1;
	for(int j = 0;j < scan_col; j++)
	{
		flag = 0;
		for(int mi = j;mi < m;mi++)
			input_data.mat[flag++][0] = input_Matrix->mat[mi][j];
		//select one column use Householder
		input_len = m - j;
		HouseholderMatrix(&input_data, input_len, &mat_v, &beta);
		//compute A(j:m,j:n)'*v
		for(int mi = 0; mi < m - j; mi++)
			for(int nj = 0; nj < n - j; nj++)
				temp_mat1.mat[mi][nj] = input_Matrix->mat[mi + j][nj + j];

		matmult_size[0] = m - j; matmult_size[1] = n - j; matmult_size[2] = 1;
		getMatTranMat(&temp_mat1, &mat_v, matmult_size, &At_v);
		// compute w = beta*A'*v
		mat_size[0] = n - j; mat_size[1] = 1;
		getDotMultMatrix(&At_v, beta, &W_b_At_v, mat_size);
		// compute temp_mat1 = v*w'
		matmult_size[0] = m - j; matmult_size[1] = 1; matmult_size[2] = n - j;
		for(int mi = 0;mi < W_b_At_v.m;mi++)
			Wt_b_At_v.mat[0][mi] = W_b_At_v.mat[mi][0];

		getMatMultMat(&mat_v, &Wt_b_At_v, matmult_size, &v_wt, 1);
		// compute B = H*A =  A - v*w'
		mat_size[0] = m - j; mat_size[1] = n - j;
		getSubMat(&temp_mat1, &v_wt, mat_size, &A_v_wt);
		//use A_v_wt cover part of input_Matrix
		for(int mi = 0; mi < m - j;mi++)
			for(int nj = 0; nj < n - j;nj++)
				input_Matrix->mat[mi + j][nj + j] = A_v_wt.mat[mi][nj];
	}//end for(int j = 0;j < scan_col; j++)
	freeMatrix(&input_data);
	freeMatrix(&mat_v);
	freeMatrix(&W_b_At_v);
	freeMatrix(&Wt_b_At_v);
	freeMatrix(&At_v);
	freeMatrix(&v_wt);
	freeMatrix(&A_v_wt);
	freeMatrix(&temp_mat1);
}

/*
 * illustration:  more efficient than QRDecompose function, but Incomprehensible.
 */
void QRDecomposeA(MYMatrix *input_Matrix)
{
	MYINT m = input_Matrix->m, n = input_Matrix->n, flag = 0;
	MYINT input_len = 0,scan_col = n;
	MYDOUBLE *input_data = NULL, *v = NULL;
	MYDOUBLE W_b_At_v = 0, vwt = 0, beta = 0.0;
	// m mast great than n
	//if (m < n) return ;
	// malloc memory one time
	input_data = ( MYDOUBLE * )malloc( m * sizeof( MYDOUBLE ) );
	v = ( MYDOUBLE * )malloc( m * sizeof( MYDOUBLE ) );
	if(m == n) scan_col = n - 1;
	for(int j = 0;j < scan_col; j++)
	{
		flag = 0;
		for(int mi = j;mi < m;mi++)
			input_data[flag++] = input_Matrix->mat[mi][j];
		//select one column use Householder
		input_len = m - j;
		Householder(input_data, input_len, v, &beta);
		for(int mi = 0; mi < n - j; mi++)
		{
			// compute w = beta*A'*v
			W_b_At_v = 0; vwt = 0;
			for(int nj = 0; nj < m - j; nj++)
			{
				W_b_At_v += input_Matrix->mat[nj + j][mi + j] * v[nj];
			}
			W_b_At_v = beta * W_b_At_v;
			for(int ki = 0; ki < m-j; ki++)
			{
				// compute temp_mat1 = v*w'
				vwt = v[ki] * W_b_At_v;
				//A =  A - v*w'
				input_Matrix->mat[ki + j][mi + j] = input_Matrix->mat[ki + j][mi + j] - vwt;
			}
		}
	}//end for(int j = 0;j < scan_col; j++)
	free(input_data);
	free(v);
}

void QREigenFun(MYMatrix *input_Matrix)
{
	HouseholderQR<MatrixXd> qr;
	MatrixXd eigenMat, R;
	eigenMat.resize(input_Matrix->m, input_Matrix->n);
	for(int i = 0;i < input_Matrix->m;i++)
		for(int j = 0;j < input_Matrix->n;j++)
			eigenMat(i,j) = input_Matrix->mat[i][j];
	qr.compute(eigenMat);
	R = qr.matrixQR().triangularView<Upper>();
	for(int i = 0;i < input_Matrix->m;i++)
			for(int j = 0;j < input_Matrix->n;j++)
				input_Matrix->mat[i][j] = R(i,j);

}

/*illustration: compute beta multiply matrix *
 *example:
 *		beta=2;
 *		matrix=[1 1 1;2 2 2];
 *		mat_size = [2 3];
 *		output_matrix=beta*matrix=[2 2 2;4 4 4];
 *Input:
 *		matrix: size m*n (double)
 *		mat_size: size 1*2 (double)
 *		beta: size 1 (double)
 *Output:
 *		output_matrix: size m*n (double)
 */
void getDotMultMatrix(MYMatrix *matrix, MYDOUBLE beta, MYMatrix *output_matrix, MYINT *mat_size)
{
	MYINT m = matrix->m, n = matrix->n;
	if(matrix->m != output_matrix->m || matrix->n != output_matrix->n)
	{
		TRACE("getDotMultMatrix\n");
		return ;
	}
	if(NULL != mat_size)
	{
		m = mat_size[0];
		n = mat_size[1];
	}
	for(int i = 0;i < m; i++)
		for(int j = 0;j < n; j++)
			output_matrix->mat[i][j] = matrix->mat[i][j] * beta;
}

/*illustration: Matrix subtraction
 *
 *example:
 *		matrix1=[1 2 3;2 2 2];
 *		matrix2=[1 2 3;1 1 1];
 *		output_matrix=matrix1 - matrix2 = [0 0 0;1 1 1];
 *Input:
 *		matrix1: size m*n (double)
 *		matrix2: size m*n (double)
 *		mat_size: size 1*2 (double)
 *Output:
 *		output_matrix: size m*n (double)
 */
void getSubMat(MYMatrix *matrix1, MYMatrix *matrix2, MYINT *mat_size, MYMatrix *output_matrix)
{
	MYINT m = matrix1->m, n = matrix1->n;
	if(matrix1->m != matrix2->m || matrix1->n != matrix2->n)
	{
		TRACE("getSubMat");
		return ;
	}
	if(NULL != mat_size)
	{
		m = mat_size[0];
		n = mat_size[1];
	}
	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++)
			output_matrix->mat[i][j] = matrix1->mat[i][j] - matrix2->mat[i][j];
}

/*
 * illustration: use householder Transformation Vector
 * H = I - beta*v*v';
 * H*x = x - v*w' (w = beta*x'*v)
 * example:
 * 		x = [3,4,5]
 * 		H*x = [7.07 0 0] (7.07 is norm(x))
 * 		H = [0.42 0.57 0.71; 0.57 0.44 -0.69; 0.71 -0.69 0.13]
 * 		beta = 0.576
 * 		v = [1 -0.98 -1.23]
 * Input:
 * 		input_data:size 1*n target vector (double)
 * 		data_len: size 1 (double): length of input_data and v
 * output:
 * 		output_data: size 1 (double): The first number after the householder Transformation
 * 		v: size 1*n (double):Generating transformation matrix H
 * 		beta:size 1 (double)
 * reference: 数值线性代数（徐树芳）P88
 */
void Householder(MYDOUBLE *input_data, MYINT data_len,MYDOUBLE *v, MYDOUBLE *beta)
{
	MYDOUBLE zgama = 0.0, input_data_max = 0.0, max_index = -1,
			alpha = 0.0, tempVar = 0.0;
	//judge input_data is single number
	if(data_len == 1) {
		*v = 0;
		*beta = 0;
	}

	input_data_max = getAbsMax(input_data, data_len, NULL);
	tempVar = input_data[0]*input_data[0];
	for(int i = 1; i < data_len;i++)
	{
		zgama += input_data[i]*input_data[i];
		v[i] = input_data[i] / input_data_max;
	}
	v[0] = 1;
	alpha = sqrt(tempVar + zgama) / input_data_max;
	zgama = zgama / (input_data_max * input_data_max);

	if(input_data[0] <= 0)
		v[0] = input_data[0]/input_data_max - alpha;
	else
		v[0] = -zgama / (input_data[0]/input_data_max + alpha);
	*beta = 2 * v[0] * v[0] / (zgama + v[0] * v[0]);
	tempVar = v[0];
	for(int i = 0; i < data_len;i++)
		v[i] = v[i] / tempVar;
}

/*
 * illustration: use householder Transformation Matrix
 * Input:
 * 		input_data:size 1*n target vector (Matrix)
 * 		data_len: size 1 (double): length of input_data and v
 * output:
 * 		v: size 1*n (Matrix):Generating transformation matrix H
 * 		beta:size 1 (double)
 */
void HouseholderMatrix(MYMatrix *input_data, MYINT data_len, MYMatrix *v, MYDOUBLE *beta)
{
	MYDOUBLE zgama = 0.0, input_data_max = 0.0, max_index = -1,
			alpha = 0.0, tempVar = 0.0;
	//judge input_data is single number
	if(data_len == 1) {
		v->mat[0][0] = 0;
		*beta = 0;
	}

	input_data_max = getAbsMatrixMaxA(input_data, data_len, NULL);
	tempVar = input_data->mat[0][0]*input_data->mat[0][0];
	for(int i = 1; i < data_len;i++)
	{
		zgama += input_data->mat[0][i]*input_data->mat[0][i];
		v->mat[0][i] = input_data->mat[0][i] / input_data_max;
	}
	v->mat[0][0] = 1;
	alpha = sqrt(tempVar + zgama) / input_data_max;
	zgama = zgama / (input_data_max * input_data_max);

	if(input_data->mat[0][0] <= 0)
		v->mat[0][0] = input_data->mat[0][0] / input_data_max - alpha;
	else
		v->mat[0][0] = -zgama / (input_data->mat[0][0]/input_data_max + alpha);
	*beta = 2 * v->mat[0][0] * v->mat[0][0] / (zgama + v->mat[0][0] * v->mat[0][0]);
	tempVar = v->mat[0][0];
	for(int i = 0; i < data_len;i++)
		v->mat[0][i] = v->mat[0][i] / tempVar;
}

/*illustration: Get the maximum value of the vector
 *
 *example:
 *		input_data = [1 3 2 1.2]
 *		data_len = 4 (length of input_data)
 *		max_number = 3 (return)
 *		max_index = 2
 *Input:
 *		input_data: size 1*n (double)
 *		data_len: size 1 (double): length of input_data
 *Output:
 *		max_index: size 1 (int): index maximum value of the input_data
 *		max_number: size 1 (double): maximum value of the input_data
 */
MYDOUBLE getAbsMax(MYDOUBLE *input_data, MYINT data_len,MYINT *max_index)
{
	MYDOUBLE max_number = 0.0, abs_number = 0.0;
	if(input_data == NULL) return MYEPS;
	max_number = input_data[0] > 0 ? input_data[0]: -input_data[0];
	for(int i = 0;i < data_len;i++)
	{
		abs_number = input_data[i] > 0 ? input_data[i]: -input_data[i];
		if( abs_number >= max_number)
		{
			max_number = abs_number;
			if(max_index != NULL)
				*max_index = i;
		}
	}

	return max_number;
}

/*illustration: Get the maximum value of the vector
 *
 *Input:
 *		input_data: size n*1 (MYMatrix)
 *		data_len: size 1 (double): length of input_data
 *Output:
 *		max_index: size 1 (int): index maximum value of the input_data
 *		max_number: size 1 (double): maximum value of the input_data
 */

MYDOUBLE getAbsMatrixMax(MYMatrix *input_data, MYINT data_len,MYINT *max_index)
{
	MYDOUBLE max_number = 0.0, abs_number = 0.0;
	if(input_data == NULL) return MYEPS;
	max_number = input_data->mat[0][0] > 0 ? input_data->mat[0][0]: -input_data->mat[0][0];
	for(int i = 0;i < data_len;i++)
	{
		abs_number = input_data->mat[i][0] > 0 ? input_data->mat[i][0]: -input_data->mat[i][0];
		if( abs_number >= max_number)
		{
			max_number = abs_number;
			if(max_index != NULL)
				*max_index = i;
		}
	}

	return max_number;
}

/*illustration: Get the maximum value of the vector
 *
 *Input:
 *		input_data: size 1*n (MYMatrix)
 *		data_len: size 1 (double): length of input_data
 *Output:
 *		max_index: size 1 (int): index maximum value of the input_data
 *		max_number: size 1 (double): maximum value of the input_data
 */

MYDOUBLE getAbsMatrixMaxA(MYMatrix *input_data, MYINT data_len,MYINT *max_index)
{
	MYDOUBLE max_number = 0.0, abs_number = 0.0;
	if(input_data == NULL) return MYEPS;
	max_number = input_data->mat[0][0] > 0 ? input_data->mat[0][0]: -input_data->mat[0][0];
	for(int i = 0;i < data_len;i++)
	{
		abs_number = input_data->mat[0][i] > 0 ? input_data->mat[0][i]: -input_data->mat[0][i];
		if( abs_number >= max_number)
		{
			max_number = abs_number;
			if(max_index != NULL)
				*max_index = i;
		}
	}

	return max_number;
}

/*illustration: Get matrix Transposition products other matrix
 *
 *example:
 *		input_mat1 = [1 2;3 1;2 4]
 *		input_mat2 = [3 1;2 1;1 1]
 *		matmult_len = [3 2 2]
 *		output_mat = input_mat1' * input_mat1
 *		output_mat = [11 6; 12 7]
 *Input:
 *		input_mat1: size n*m (double)
 *		input_mat2: size n*k (double)
 *		matmult_len: size 1*3 (int): length of input_mat1 and input_mat2:
 *		matmult_len  = [n m k]
 *Output:
 *		output_mat: size m*k (double): index maximum value of the input_data
 *
 */
void getMatTranMat(MYMatrix *input_mat1, MYMatrix *input_mat2, MYINT *matmult_size, MYMatrix *output_mat)
{
	MYINT m = input_mat1->n, n = input_mat1->m, k = input_mat2->n;
	MYDOUBLE *mat1_col =(MYDOUBLE *)malloc(n * sizeof(MYDOUBLE)), *mat2_col =(MYDOUBLE *)malloc(n * sizeof(MYDOUBLE));
	if(input_mat1->m != input_mat2->m)
	{
		TRACE("getMatTranMat");
		return ;
	}
	if(NULL != matmult_size)
	{
		m = matmult_size[1];
		n = matmult_size[0];
		k = matmult_size[2];
	}

	for(int i = 0; i < m;i++)
		for(int j = 0;j < k;j++)
		{
			//get input_mat1 column i and input_mat2 column j
			for(int c = 0; c < n;c++)
			{
				mat1_col[c] = input_mat1->mat[c][i];
				mat2_col[c] = input_mat2->mat[c][j];
			}
			output_mat->mat[i][j] = getVectorDot(mat1_col,mat2_col,n);
		}
	free(mat1_col);
	free(mat2_col);
}


/*illustration: Get two matrix products
 *
 *example:
 *		input_mat1 = [1 3 2;2 1 4]
 *		input_mat2 = [3 1;2 1;1 1]
 *		matmult_len = [2 3 2]
 *		output_mat = beta*input_mat1 * input_mat1
 *		output_mat = [11 6; 12 7]
 *Input:
 *		input_mat1: size m*n (double)
 *		input_mat2: size n*k (double)
 *		matmult_size: size 1*3 (int): length of input_mat1 and input_mat2:
 *		matmult_size  = [m n k]
 *		beta: coefficient of input_mat1*input_mat2
 *Output:
 *		output_mat: size m*k (double): index maximum value of the input_data
 *
 */
void getMatMultMat(MYMatrix *input_mat1, MYMatrix *input_mat2, MYINT *matmult_size, MYMatrix *output_mat, MYDOUBLE beta)
{
	MYINT m = input_mat1->m, n = input_mat1->n, k = input_mat2->n;
	MYDOUBLE *mat1_row =(MYDOUBLE *)malloc(n * sizeof(MYDOUBLE)), *mat2_col =(MYDOUBLE *)malloc(n * sizeof(MYDOUBLE));

	if(input_mat1->n != input_mat2->m)
	{
		TRACE("getMatTranMat");
		return ;
	}
	if(NULL != matmult_size)
	{
		m = matmult_size[0];
		n = matmult_size[1];
		k = matmult_size[2];
	}

	for(int i = 0; i < m;i++)
		for(int j = 0;j < k;j++)
		{
			//get input_mat1 Line i and input_mat2 column j
			for(int c = 0; c < n;c++)
			{
				mat1_row[c] = input_mat1->mat[i][c];
				mat2_col[c] = input_mat2->mat[c][j];
			}
			output_mat->mat[i][j] = beta * getVectorDot(mat1_row,mat2_col,n);
		}
	free(mat1_row);
	free(mat2_col);
}

/*illustration: Get the multiplication value of the two vector
 *
 *example:
 *		vct_a = [1 3 5]
 *		vct_b = [2 4 6]
 *		vct_len = 3 (length of input_data)
 *		mult_res=1*2 + 3*4 + 5*6
 *Input:
 *		vct_a: size 1*n (double)
 *		vct_b: size 1*n (double)
 *		vct_len: size 1 (double): length of vct_a
 *Output:
 *		mult_res: size 1 (double): multiplication value of the vct_a*vct_b
 */
MYDOUBLE getVectorDot(MYDOUBLE *vct_a,MYDOUBLE *vct_b, MYINT vct_len)
{
	MYDOUBLE mult_res = 0.0;
	for(int i = 0;i < vct_len; i++)
		mult_res = mult_res + vct_a[i] * vct_b[i];
	return mult_res;
}

/*illustration: Get identity matrix
 *
 *example:
 *		matrix=[0 0 0;0 0 0];
 *		output matrix=[1 0 0;0 1 0];
 *Input:
 *		matrix: size m*n (double): The element is all zero
 *		mat_row: size 1 (double): row of matrix
 *		mat_clo: size 1 (double): row of column
 *Output:
 *		matrix: size m*n (double): The matrix is identity
 */
void getIdentityMat(MYMatrix *matrix, MYINT *mat_size)
{
	MYINT mat_row = matrix->m, mat_col = matrix->n;
	MYINT sqruare = 0;
	if(NULL != mat_size)
	{
		mat_row = mat_size[0];
		mat_col = mat_size[1];
	}

	sqruare = (mat_row>mat_col) ? mat_col:mat_row;
	for(int i = 0;i < mat_row; i++)
		for(int j = 0;j < mat_col; j++)
			matrix->mat[i][j] = 0;
	for(int i = 0;i < sqruare; i++)
		matrix->mat[i][i] = 1;
}


void mallocMatrix(MYMatrix *matrix, MYINT m, MYINT n)
{
	matrix->mat = (MYDOUBLE **)malloc(m * sizeof(MYDOUBLE *));
	for(int i = 0;i < m;i++)
		matrix->mat[i] = ( MYDOUBLE *)malloc(n * sizeof(MYDOUBLE));
	matrix->m = m;
	matrix->n = n;
	for(int i = 0;i < matrix->m;i++)
		for(int j = 0;j < matrix->n;j++)
			matrix->mat[i][j] = 0;
}
void copyMatrix(const MYMatrix *matrix1, MYMatrix *matrix2)
{
	if(matrix1->m != matrix2->m || matrix1->n != matrix2->n)
	{
		TRACE("copyMatrix Error\n");
		return ;
	}
	for(int i = 0;i < matrix1->m;i++)
		for(int j = 0;j < matrix1->m;j++)
			matrix2->mat[i][j] = matrix1->mat[i][j];
}

void freeMatrix(MYMatrix *matrix)
{
	for(int i = 0;i < matrix->m;i++)
		free(matrix->mat[i]);
	free(matrix->mat);
	matrix->m = 0;
	matrix->n = 0;
}

void printMatrix(MYMatrix *matrix)
{
	for(int i = 0;i < matrix->m;i++)
	{
		for(int j = 0;j < matrix->n;j++)
			printf("%lf ",matrix->mat[i][j]);
		printf("\n");
	}
}









