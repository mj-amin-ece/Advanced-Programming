#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include"Matrix.h"
#include<optional>
#include"aphw2.h"

std::optional<double> det( Matrix& A )   // return determinant of the given matrix
{
	return std::optional<double> {A.det()};
}

std::optional<Matrix> inv(Matrix& A)             //return inverse of the given matrix
{
	std::array<size_t, 2> size_matrix{A.getSize()};
	if (size_matrix[0] != size_matrix[1])     //check  matrix is the squre form or not 
		return std::nullopt;      // same as return { };

	return std::optional<Matrix>{A.inv()};
}

std::optional<Matrix> transpose(Matrix& A)    //return the transpose of the matrix
{
	return std::optional<Matrix>{A.T()};
}
 
std::vector<std::vector<double>> getData(const char* filename, bool add_bias)   //get data from a .csv file
{
	std::ifstream input_file{ filename };   //  read .csv file
	std::vector<std::vector<double>> data_vector{};   //for store data

	while (!input_file.eof())    // while until end of file
	{
		std::string line{};       // for store each line
		std::string data{};       // for store each data
		std::vector<double> row{};  // for store each row

		std::getline(input_file, line);  // store each line 

		if (static_cast<int>(line[0]) == 0)  // if line is empty break from loop
			break;
		if (add_bias)      // add bias or not
			row.push_back(1.);
		for (size_t i = 0; i < line.length(); i++)  // to get data from a line
		{
			if (line[i] != ',')
				data += line[i];
			else
			{
				row.push_back(std::stod(data));   // store data
				data = "";
			}
		}
		row.push_back(std::stod(data));   // store a row of data in a Data vector
		data_vector.push_back(row);
	}
	input_file.close();  //close file

	return data_vector;  //return data vector
}

size_t findMinNoOfMultiplications(std::vector<Matrix>& v)  // minimum number of required scalar multiplications 
{
	std::vector<std::vector<size_t>> table{};     // for store m[i,j]
	size_t step{};

	for (size_t i = 0; i < v.size(); i++)   //make a table with elements of zero
	{
		std::vector<size_t> row(v.size());   // for store a row elements
		table.push_back(row);                // store a row elements of zero
	}
	while (step != v.size()-1)       //continue until fill the table
	{
		for (size_t i = 0; i < v.size(); i++)
		{
			for (size_t j = i + step + 1; j < v.size(); j++)  //step 1
			{
				if (j - i == 1)
				{
					table[i][j] = v[i].getSize()[0] * v[i].getSize()[1] * v[j].getSize()[1];    //comput the m[i,j]: j-i=1
					break;   // got next step
				}
				else  //j-i>1
				{
					size_t min{};  // min multipy
					bool  ful{ false };  //for initial min
					for (size_t k = i; k < j; k++)
					{
						size_t temp{};
						temp = table[i][k] + table[k + 1][j] + (v[i].getSize()[0]) * v[k].getSize()[1] * v[j].getSize()[1];   //compute the m[i,j]
						if (!ful)  //initial min
						{
							ful = true;   //show it is first temp or not
							min = temp;  // first temp is first min
						}
						min = min > temp ? temp : min;   //find min
					}
					table[i][j] = min;   //fill the table with min
					break;  // go to next step
				}
			}
		}
		step++;
	}
	return table[0][v.size() - 1]; // return minimum number of multiplications 
}

Matrix findWeights(const char* name_file)  //find weights
{
	Matrix data{getData(name_file,true)}; // get data from .csv file as a matrix
	Matrix Y{ data.col(7) };  // get real grade as a matrix
	Matrix X{ data.delCol(7) };  // get feature as a matrix
	Matrix W{ 7,1,false };  //define and initial weights matrix
	W = Matrix{ X.T() * X}.inv()*X.T() * Y;  //calculate weights
	
	return W; //return weights as a matrix 
}

Matrix predict(const char* name_file, Matrix& W, bool disp) // calculate predict grade and show them
{
	Matrix data{ getData(name_file,true) };    //get data as a matrix
	Matrix Y{ data.col(7) };   // get real grade as a matrix
	Matrix X{ data.delCol(7) };  // get feature as a matrix
	Matrix pridict_grade{ X * W };  //predict grade and save as a matrix

	if (disp)  //to display predict grade and real grade
	{
		std::cout << "No" << std::setw(28) << "Real Grade" << std::setw(25) << "Estimated Grade" << std::endl;
		for (size_t i = 0; i < 28; i++)
			std::cout << "**";
		std::cout << std::endl;

		for (size_t i = 0; i < pridict_grade.getSize()[0]; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (j == 0)  //number of studen
					std::cout << std::setiosflags(std::ios::left) << std::setw(20) << i + 1;
				if (j == 1)
					std::cout << std::setw(20) << Y[i][0]; //real grade
				if (j == 2)
					std::cout << std::setw(20) << pridict_grade[i][0];  //predict garde
			}
			std::cout << std::endl;
		}
	}

	return pridict_grade; //return predict grade as a matrix
}