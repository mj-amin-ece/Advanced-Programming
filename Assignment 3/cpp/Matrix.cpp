#include "Matrix.h"


double det_funtion(std::vector<std::vector<double>>, size_t);

Matrix::Matrix(std::vector<std::vector<double>> data)
{
	Data = data;   // copy each elemnt of data to Matrix
	size[1] = Data[0].size();     //size of matrix
	size[0] = Data.size();
}

Matrix::Matrix(size_t m, size_t n, bool ones)
{
	size[0] = m;   //size of matrix
	size[1] = n;
	for (size_t row = 0; row < size[0]; row++)
	{
		std::vector<double> vector_row{};   //for store row of data

		for (size_t column = 0; column < size[1]; column++)
		{
			if (ones)
				vector_row.push_back(1);   //put one in vector
			else
				vector_row.push_back(0);   //put zero in vector
		}
		Data.push_back(vector_row);    //save row of data
	}
}

Matrix::Matrix(const Matrix& mat)   // copy constructor
{
	size[0] = mat.size[0];     //copy size
	size[1] = mat.size[1];
	Data = mat.Data;          // copy matrix
}

Matrix::Matrix(std::unique_ptr<std::unique_ptr<double[]>[]>& data, size_t m, size_t n)
{
	size[0] = m;   // size of matrix
	size[1] = n;
	for (size_t row = 0; row < size[0]; row++)   //row
	{
		std::vector<double> vector_row{};   //for store row of data

		for (size_t column = 0; column < size[1]; column++)    //column
			vector_row.push_back(data[row][column]);    //store data
		Data.push_back(vector_row);     //store a row of data
	}
}

Matrix::Matrix()  //default constructor
{
	size[0] = 0;       // size of matrix
	size[1] = 0;
	Data = {};     //empty matrix
}

std::array<size_t, 2> Matrix::getSize()    // to show size of matrix
{
	return std::array<size_t, 2>{size[0], size[1]};    //  return size of matrix
}

double Matrix::det()        //determinant of the matrix
{
	if (size[0] != size[1])               //check  matrix is the squre form or not
	{
		std::cout << "the matrix is not in the square form " << std::endl;
		return 0.0;
	}
	else
		return det_funtion(Data, size[0]);    //return determinant of the matrix
}

Matrix Matrix::inv()                    // inverse of the matrix
{
	if (size[0] != size[1])          //check  matrix is the squre form or not
	{
		Matrix inverse{ size[0], size[1], false };
		std::cout << "the matrix is not in the square form " << std::endl;
		return  inverse;                   // if it's not square form return a martix with zero elemnt 
	}

	else if (size[0] == 2)                // inverse of matrix 2*2
	{
		Matrix inverse{ 2,2,false };
		Matrix data_inverse{ Data };

		inverse[0][0] = data_inverse[1][1] / data_inverse.det();
		inverse[0][1] = -data_inverse[0][1] / data_inverse.det();
		inverse[1][0] = -data_inverse[1][0] / data_inverse.det();
		inverse[1][1] = data_inverse[0][0] / data_inverse.det();

		return inverse;
	}

	else     // inverse of matrix n*n, n>2
	{
		std::vector<std::vector<double>> inverse_vector{};  // to store of inverse matrix

		for (size_t i = 0; i < size[0]; i++)    //row of matrix
		{
			std::vector<double> inverse_vector_row{};           // for give each row to 2d vector inverse

			for (size_t j = 0; j < size[1]; j++)     //column of matrix
			{
				std::vector<std::vector<double>> temp_vector{};     // for compute det each element

				for (size_t k = 0; k < size[0]; k++)      // to get matrix of minors   //row
				{
					std::vector<double> temp_vector_row{};        // for give each row for compute det
					bool flag{ false };                 // for  showing  push back is done or not 

					for (size_t l = 0; l < size[1]; l++)   // to get matrix of minors   //column
					{
						if (k != i && l != j)  //  Copying into temporary matrix only those element  which are not in given row and column 
						{
							temp_vector_row.push_back(Data[l][k]);     // data must be transpose(adjugate matrix)
							flag = true;
						}
					}
					if (flag)
						temp_vector.push_back(temp_vector_row);       //to store matrix of minors  
				}
				Matrix temp_2{ temp_vector };

				inverse_vector_row.push_back(temp_2.det() * std::pow(-1, i + j) / Matrix{ Data }.det());  // claculate cofators and multiply by 1/determinat
			}
			inverse_vector.push_back(inverse_vector_row);          // to store inverse matrix
		}

		return Matrix{ inverse_vector };   //return matrix inverse
	}
}

Matrix Matrix::T()     // change row and column eith each other
{
	std::vector<std::vector<double>> transpose_vector{};    // to store transpose element 

	for (size_t i = 0; i < size[1]; i++)      // column
	{
		std::vector<double> transpose_vector_row{};

		for (size_t j = 0; j < size[0]; j++)      // row
			transpose_vector_row.push_back(Data[j][i]);         //changing row and column of each element and store it
		transpose_vector.push_back(transpose_vector_row);
	}

	return Matrix{ transpose_vector };   // return taranspose matrix
}

void Matrix::show()   // showing matrix
{
	for (size_t i = 0; i < size[0]; i++)    //row
	{
		for (size_t j = 0; j < size[1]; j++)     //column
			std::cout << std::setw(10) << Data[i][j];   // print each element
		std::cout << std::endl;
	}
}

Matrix Matrix::delCol(size_t k)    //remove ith column
{
	std::vector<std::vector<double>> remain_vector{};  // to store remain elements 

	for (size_t i = 0; i < size[0]; i++)    //row
	{
		std::vector<double> remain_vector_row{};

		for (size_t j = 0; j < size[1]; j++)   //column
			if (j != k)      // for removes element which has i-th column 
				remain_vector_row.push_back(Data[i][j]);  // store  remaining element 
		remain_vector.push_back(remain_vector_row);
	}
	//Data = remain_vector;     // store ramain elements of matrix
	//size[0] = Data.size();     // store size of remain matrix
	//size[1] = Data[0].size();

	return Matrix{remain_vector};      // return remaining matrix
}

Matrix Matrix::remain_matrix_until_col(size_t k)          //removes the given (k+1-th) columns and and after that of the matrix
{
	std::vector<std::vector<double>> remain_vector{};     // to store remain elements 

	for (size_t i = 0; i < size[0]; i++)                  //row
	{
		std::vector<double> remain_vector_row{};          //to store a row of element

		for (size_t j = 0; j <= k; j++)                   // save element in  zero to i-th column
			remain_vector_row.push_back(Data[i][j]);      // store  remaining element 
		remain_vector.push_back(remain_vector_row);       // store a row of element
	}

	return Matrix{ remain_vector };                       // return remaining matrix
}

Matrix Matrix::col(size_t k)   //return i-th column
{
	std::vector<std::vector<double>> column{};  // to store elements of i-th column

	for (size_t i = 0; i < size[0]; i++)      //row
	{
		std::vector<double> temp{};
		temp.push_back(Data[i][k]);   // store elements if i-th column
		column.push_back(temp);
	}

	return Matrix{ column };         // return column i-th as a new matrix 
}

Matrix Matrix::remain_matrix_after_col(size_t k)           //removes columns until (k-1-th) columns of the matrix
{
	std::vector<std::vector<double>> remain_vector{};      // to store remain elements 

	for (size_t i = 0; i < size[0]; i++)                   //row
	{
		std::vector<double> remain_vector_row{};           //to store a row of element

		for (size_t j = k; j < size[1]; j++)               //save element which in column k and after that     
				remain_vector_row.push_back(Data[i][j]);   // store  remaining element 
		remain_vector.push_back(remain_vector_row);        // store a row of element 
	}

	return Matrix{ remain_vector };                       // return remaining matrix
}

Matrix Matrix::re_row(size_t k)                                     //return a row
{
	return Matrix{ std::vector<std::vector<double>>{Data[k]} };    // return k-th row as a matrix
}

Matrix Matrix::del_last_row()
{
	std::vector<std::vector<double>> remain_vector{};  // to store remain elements 

	for (size_t i = 0; i < size[0]-1; i++)            //row
		remain_vector.push_back(Data[i]);             //save row of matrix

	return Matrix{ remain_vector };                  // return remaining matrix
}

Matrix Matrix::attach(const Matrix& A)                              //attach to matrix
{
	if (size[0] != A.size[0])                                       //the numbers of two matrix must be same
	{
		std::cout << " can not to attech" << std::endl;            
		return Matrix{};
	}

	Matrix result{ size[0],size[1] + A.size[1],false };             //make a new matrix to save attached of two matrixs

	for (size_t i = 0; i < A.size[0]; i++)                          //row
	{
		for (size_t j = 0; j < size[1]; j++)                        //column of first matrix
			result[i][j] = Data[i][j];                              //save element of first matrix
		for (size_t j = size[1]; j < A.size[1] + size[1]; j++)      //column of second matrix
			result[i][j] = A.Data[i][j-size[1]];                    //save element of second matrix
	}

	return result;                                                  //return attached of two matrixs
}

void Matrix::save(const char* name)    // save matrix as a .csv file
{
	std::ofstream out{ name };    //  write .csv file

	for (size_t i = 0; i < size[0]; i++)   // rows
	{
		for (size_t j = 0; j < size[1]; j++)  // columns
			out << Data[i][j] << ',';             // print each elements of matrix
		out << std::endl;
	}
	out.close();   // close file
}

void Matrix::load(const char* name)    // loading matrix from .csv file
{
	std::ifstream input_file{ name };    //  read .csv file

	while (!input_file.eof())           // while until end of file
	{
		std::string line{};               // for store each line
		std::string data{};               // for store each data
		std::vector<double> row{};      // for store each row

		std::getline(input_file, line);   // store each line 
		if (static_cast<int>(line[0]) == 0)   // if line is empty break from loop
			break;
		for (size_t i = 0; i < line.length(); i++)    // to get data from a line
		{
			if (line[i] != ',')   // continue to get a data
				data += line[i];
			else
			{
				row.push_back(std::stod(data));       // store data
				data = "";
			}
		}
		row.push_back(std::stod(data));
		Data.push_back(row);              // store a row of data in a Data vector
	}
	;
	size[0] = Data.size();             // store matrix size
	size[1] = Data[0].size();

	input_file.close();    //close file
}

Matrix Matrix::operator+(const Matrix& A)       // for add matrix
{
	if (size[0] != A.size[0] || size[1] != A.size[1])    // two matrix must have same dimension
	{
		throw std::invalid_argument(" dimensions not correct");
		return Matrix{};
	}

	std::vector<std::vector<double>> sum_vector{};       // for store sum of elements of each matrix

	for (size_t i = 0; i < size[0]; i++)           // row
	{
		std::vector<double> sum_row{};     // for store row of data

		for (size_t j = 0; j < size[1]; j++)   //column
			sum_row.push_back(Data[i][j] + A.Data[i][j]);    //store sum of elements 
		sum_vector.push_back(sum_row);                //store row vector
	}

	return Matrix(sum_vector);    //return sum matrix
}

Matrix Matrix::operator-(const Matrix& A)  // for subtraction matrixs
{
	if (size[0] != A.size[0] || size[1] != A.size[1])  // two matrix must have same dimension
	{
		throw std::invalid_argument(" dimensions not correct");
		return Matrix{};
	}

	std::vector<std::vector<double>> subtraction_vector{};    // for store subtraction of elements of each matrix

	for (size_t i = 0; i < size[0]; i++)   //row
	{
		std::vector<double> sum_row{}; // for store row of data

		for (size_t j = 0; j < size[1]; j++)    //column
			sum_row.push_back(Data[i][j] - A.Data[i][j]);  //store subtraction of elements 
		subtraction_vector.push_back(sum_row);       //store row vector
	}

	return Matrix(subtraction_vector);   //return subtraction matrix
}

Matrix Matrix::operator*(const Matrix& B)    //matrix multiplication
{
	if (size[1] != B.size[0])  // A  has dimensions m×n and B has dimensions n×p
	{
		throw std::invalid_argument(" dimensions not correct");
		return Matrix{};
	}

	std::vector<std::vector<double>> multiply_vector{};    // for store  data of multiply matrix

	for (size_t i = 0; i < size[0]; i++)   // row matrix A
	{
		std::vector<double> multiply_vector_row{};        // for store  row of data 
		for (size_t j = 0; j < B.size[1]; j++)     // column martix B 
		{
			double temp{};

			for (size_t k = 0; k < size[1]; k++)
				temp += Data[i][k] * B.Data[k][j];    //multiplying row  i  of  A  by column  j  of  B
			multiply_vector_row.push_back(temp);       //sotre a row data
		}
		multiply_vector.push_back(multiply_vector_row);   //store data of matrix
	}

	return Matrix{ multiply_vector };    //return of multiply matrix
}

std::vector<double>& Matrix::operator[](size_t row)  //overload operator[] to return a reference to an object that represents the row                                                   
{                                                // and with itself has an appropriate operator[]
	return Data[row];
}

double det_funtion(std::vector<std::vector<double>> v, size_t n)     //Recursive function for finding determinant of matrix
{
	double determinant{};

	if (n == 1)
	{
		std::cout << " inavalid matrix" << std::endl;
		return 0;
	}
	else if (n == 2)
		return (v[0][0] * v[1][1]) - (v[0][1] * v[1][0]);       //determinant matrix  2*2
	else
	{
		for (size_t i = 0; i < n; i++)                           // loop to get cofactor for each element of matrix
		{
			std::vector<std::vector<double>> det_vector{};     // to store elemnt of matrix of minors

			for (size_t a = 0; a < n; a++)        //to get matrix of minors   //row
			{
				std::vector<double> det_vector_row{};
				bool flag{ false };                    // for  showing  push back is done or not 

				for (size_t b = 0; b < n; b++)    // column
				{
					if (a != 0 && b != i)     //  Copying into temporary matrix only those element  which are not in given row and column 
					{
						det_vector_row.push_back(v[a][b]);
						flag = true;
					}
				}
				if (flag)
					det_vector.push_back(det_vector_row);   //To store matrix of minors
			}
			determinant += (std::pow(-1, i) * v[0][i] * det_funtion(det_vector, n - 1));    //calculalte cofactors and  determinant by algorithm recursive determinant
		}
		return determinant;
	}
}
