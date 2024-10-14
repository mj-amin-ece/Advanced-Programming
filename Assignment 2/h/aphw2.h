#pragma once
#include"Matrix.h"
#include<optional>

std::optional<double> det(Matrix&);     // return determinant of the given matrix
std::optional<Matrix> inv(Matrix&);      //return inverse of the given matrix
std::optional<Matrix> transpose(Matrix&);   //return the transpose of the matrix
std::vector<std::vector<double>> getData(const char* filename, bool add_bias=true);  //to get data
size_t findMinNoOfMultiplications(std::vector<Matrix>& v);  // minimum number of required scalar multiplications 
Matrix findWeights(const char*);               // return the proper weights
Matrix predict(const char*, Matrix& w, bool disp = false );    //return the estimated outputs