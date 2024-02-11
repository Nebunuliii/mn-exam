#pragma once

#include <iostream>
#include <vector>
#include <functional>

#define PI std::acos(-1)

using matrix = std::vector<std::vector<double>>;
using vector = std::vector<double>;

struct complex
{
	double real, imaginary;
};

complex sumOf(const complex& a, const complex& b)
{
	return { a.real + b.real, a.imaginary + b.imaginary };
}

complex productOf(const complex& a, const complex& b)
{
	return { a.real * b.real - a.imaginary * b.imaginary, 
			 a.real * b.imaginary + a.imaginary * b.real };
}

complex divisionOf(const complex& a, const complex& b)
{
	return { (a.real * b.real + a.imaginary * b.imaginary) /
			 (std::pow(b.real, 2) + std::pow(b.imaginary, 2)),
			 (a.imaginary * b.real - a.real * b.imaginary) /
			 (std::pow(b.real, 2) + std::pow(b.imaginary, 2)) };
}

complex powc(const complex& c, const int& power)
{
	if (power == 0)
		return { 1, 0 };
	return productOf(c, powc(c, power - 1));
}

//m - matrix
void printm(const matrix& M)
{
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[0].size(); j++)
			std::cout << M[i][j] << " ";
		std::cout << '\n';
	}
}

//v - vector
void printv(const vector& v)
{
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << '\n';
}

//c - complex
void printc(const complex& c)
{
	std::cout << c.real << " + " << c.imaginary << "i\n";
}

matrix concatCollums(const matrix& A, const matrix& B)
{
	if (A.size() == B.size())
	{
		matrix C;
		//resize(number of vectors, number of elements in a vector)
		C.resize(A.size(), vector(A[0].size() + B[0].size()));

		for (int i = 0; i < A.size(); i++)
			for (int j = 0; j < A[0].size(); j++)
				C[i][j] = A[i][j];

		for (int i = 0; i < C.size(); i++)
			for (int j = A[0].size(); j < C[0].size(); j++)
				C[i][j] = B[i][j - A[0].size()];

		return C;
	}

	return matrix();
}

matrix concatRows(const matrix& A, const matrix& B)
{
	if (A[0].size() == B[0].size())
	{
		matrix C;
		C.resize(A.size() + B.size(), vector(A[0].size()));

		for (int i = 0; i < A.size(); i++)
			for (int j = 0; j < A[0].size(); j++)
				C[i][j] = A[i][j];

		for (int i = A.size(); i < C.size(); i++)
			for (int j = 0; j < A[0].size(); j++)
				C[i][j] = B[i - A.size()][j];

		return C;
	}

	return matrix();
}

double sumOfElements(const matrix& M)
{
	double sum = 0;
	for (int i = 0; i < M.size(); i++)
		for (int j = 0; j < M[0].size(); j++)
			sum += M[i][j];

	return sum;
}

matrix subtractionOf(matrix A, const matrix& B)
{
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[0].size(); j++)
			A[i][j] -= B[i][j];

	return A;
}

matrix productOf(const matrix& A, const matrix& B)
{
	matrix C;
	C.resize(A.size(), vector(B[0].size()));

	for(int i = 0; i < A.size(); i++)
		for(int j = 0; j < B[0].size(); j++)
			for(int k = 0; k < A[0].size(); k++)
				C[i][j] += A[i][k] * B[k][j];

	return C;
}

matrix productOf(matrix M, const double& val)
{
	for (int i = 0; i < M.size(); i++)
		for (int j = 0; j < M[0].size(); j++)
			M[i][j] *= val;

	return M;
}

vector productOf(vector V, const double& val)
{
	for (int i = 0; i < V.size(); i++)
		V[i] *= val;

	return V;
}

matrix identityMatrix(const int& size)
{
	matrix I;
	I.resize(size, vector(size));

	for (int i = 0; i < I.size(); i++)
		for (int j = 0; j < I.size(); j++)
			if (i == j)
				I[i][j] = 1;

	return I;
}

matrix inverseOf(const matrix& M)
{
	matrix INV = concatCollums(M, identityMatrix(M.size()));
	int n = M.size(), m = 2 * n;
	for (int j = 0; j < n; j++)
	{
		for (int q = 0; q < m; q++)
			if (q > j)
				INV[j][q] = INV[j][q] / INV[j][j];
		INV[j][j] = 1;

		for (int i = 0; i < n; i++)
			if (j != i)
			{
				for (int k = 0; k < m; k++)
					if (j != k)
						INV[i][k] = INV[i][k] - INV[i][j] * INV[j][k];
				for (int k = 0; k < m; k++)
					if (j == k)
						INV[i][k] = 0;
			}
	}

	return INV;
}

matrix linearEquation(matrix A,matrix B)
{
	matrix M;
	int size = A.size();

	for (int j = 0; j < size; j++)
	{
		M = identityMatrix(size);

		M[j][j] = 1 / A[j][j];
		for (int i = 0; i < size; i++)
		{
			if (i > j)
				M[i][j] = -A[i][j] / A[j][j];
		}

		A = productOf(M, A);
		B = productOf(M, B);
	}

	matrix X = B;
	double t;

	for (int i = size - 1; i >= 0; i--)
	{
		t = 0;
		for (int j = i + 1; j < size; j++)
			t += A[i][j] * X[j][0];

		X[i][0] = B[i][0] - t;
	}
	
	return X;
}

double nonlinearEquation(double left, double right, std::function<double(double)> func)
{
	double eps = 1e-3;

	if (func(left) * func(right) > 0)
		return -1;

	double c;
	while ((right - left) > eps)
	{
		c = (left + right) * 0.5;

		if (func(c) == 0)
			return c;
		if (func(left) * func(c) > 0)
			left = c;
		else
			right = c;
	}

	return (left + right) * 0.5;
}

vector interpolation(const vector& data_x, const vector& data_y, const vector& x)
{
	vector y;
	y.resize(x.size(), 0);

	int n = data_x.size();
	int i = 0, k = 0;
	
	while (i < x.size())
	{
		for (int j = 0; j < n - 1; j++)
			if ((x[i] > data_x[j]) && (x[i] < data_x[j + 1]))
				k = j;

		y[i] = data_y[k] + ((x[i] - data_x[k]) / (data_x[k + 1] - data_x[k])) * (data_y[k + 1] - data_y[k]);
		i++;
	}

	return y;
}

double derivative(const double& x, const double& step, std::function<double(double)> func)
{
	return (func(x + step / 2) - func(x - step / 2)) / step;
}

double derivative2(const double& x, const double& step, std::function<double(double)> func)
{
	return (func(x + step) - 2 * func(x) + func(x - step)) / std::pow(step, 2);
}

double integral(const double& left, const double& right, std::function<double(double)> func)
{
	double iterations = 100;
	double h = (right - left) / iterations;

	double i = 0;
	for (int j = 0; j < iterations; j++)
	{
		double x1 = left + j * h;
		double x2 = x1 + h;

		double s = (x2 - x1) * (func(x1) + 2 * func((x1 + x2) * 0.5) + func(x2)) / 4;
		i += s;
	}

	return i;
}

vector eigenvaluesOf(const matrix& M)
{
	int size = M.size();
	matrix M_copy = M;

	vector K;
	K.resize(size);

	for (int j = 0; j < size; j++)
		for (int k = 0; k < size; k++)
			if (j == k)
				K[0] += M_copy[j][k];

	for (int i = 1; i < size; i++)
	{
		matrix TEMP = productOf(M, 
					  subtractionOf(M_copy, 
					  productOf(identityMatrix(size), 
					  K[i - 1])));
		K[i] = 0;

		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				if (j == k)
					K[i] += TEMP[j][k] / (i + 1);

		M_copy = TEMP;
	}

	return productOf(K, -1);
}