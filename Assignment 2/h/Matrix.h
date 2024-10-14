#pragma once
#include<iostream>
#include<vector>
#include <array>
#include <memory>

class Matrix
{
private :                                        //member variables
	std::vector<std::vector<double>> Data{};    // elements of matrix
	std::array<size_t, 2> size{};               //number of rows and columns
public:                                          //member functions
	Matrix(std::vector<std::vector<double>> data);      // constructors
	Matrix(size_t , size_t, bool ones = true);
	Matrix(const Matrix&);                  // copy constructor
	Matrix (std::unique_ptr<std::unique_ptr<double[]>[]>& data, size_t m, size_t n);
	Matrix();                                     // defult construactor

	std::array<size_t, 2> getSize();     //size of the matrix
	double det();            //determinant of the matrix
	Matrix inv();           // inverse of the matrix
	Matrix T();             //transpose of the matrix
	void show();             //displays the matrix
	Matrix delCol(size_t );   //removes the given (i-th) column of the matrix
	Matrix col(size_t );    //returns the given (i-th) column of the matrix
	void save(const char*);    //saves the matrix as a csv file
	void load(const char*);   //This function loads a csv file into a matrix.

	Matrix operator+(const Matrix&);    // add matrix
	Matrix operator-(const Matrix&);       //subtraction matrixs
	Matrix operator*(const Matrix&);     //multiply matrix
	std::vector <double>& operator[](int);
};
