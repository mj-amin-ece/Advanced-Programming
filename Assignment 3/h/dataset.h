#pragma once

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<time.h>
#include<vector>
#include "Matrix.h"


class Dataset
{
private:                      //Member variables
	Matrix inputs;            //Matrix of all input parts of samples of dataset
	Matrix targets;           //Matrix of all target parts of samples of dataset
	Matrix train_inputs;      //Matrix of inputs of the train part of dataset
	Matrix train_targets;     //Matrix of targets of the train part of dataset
	Matrix test_inputs;       //Matrix of inputs of the test part of dataset
	Matrix test_targets;      //Matrix of targets of the test part of dataset
	double percentage{ 70 };  //This variable tells the class how to divide data into train and test parts
	size_t no_of_samples;     //Number of all samples in the dataset
	size_t input_dim;         //Dimension of inputs of dataset
	size_t target_dim;        //Dimension of targets of dataset

public:                      
	Dataset(Matrix inputs, Matrix targets, double percentage = 70);       //Constructos
	Dataset();                                                            //Default constructor
								  	                                      //Member functions
	size_t getNoOfSamples();                                              //get number of samples
	size_t getNoOfTrainSamples();                                         //get number of train samples
	size_t getNoOfTestSamples();                                          //get number of test samples 
	size_t getInputDim();                                                 //get input dimension
	size_t getTargetDim();                                                //get target dimension
	Matrix getInputs();                                                   //get input matrix
	Matrix getTargets();                                                  //get target matrix
	Matrix getTrainInputs();                                              //get train inputs matrix
	Matrix getTrainTargets();                                             //get train target matrix
	Matrix getTestInputs();                                               //get test inputs matrix
	Matrix getTestTargets();                                              //get test targets matrix
	void shuffle();                                                       //rearranges the data samples
	void show();                                                          //show some properties of the dataset
	                                                                      //operators
	std::vector<Matrix> operator[](size_t);                               //difine operator []  
	Dataset operator+(const Dataset& dataset);                            //difine operator +
	friend std::ostream& operator<< (std::ostream& out, const Dataset& c);//difine operator <<
};
