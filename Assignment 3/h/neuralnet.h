#pragma once

#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<cmath>
#include"Matrix.h"
#include"dataset.h"
#include"result.h"


Matrix sigmoid(Matrix);            //activation function sigmoid
Matrix linear(Matrix);             //activation function linear
double d_sigmoid(double);          //drivative function sigmoid
double d_linear(double);           //drivative function linear
Matrix operator*(double, Matrix);  //opreator multipluy scaler to matrix

class NeuralNet
{
private:                             //member variable
    Matrix w1;                       // Weights of layer 1
    Matrix w2;                       // Weights of layer 2
    Matrix b1;                       // Biases of layer 1
    Matrix b2;                       // Biases of layer 2
    Matrix a1;                       // Output of layer 1
    Matrix a2;                       // Output of layer 2
    Matrix n1;                       // n vector for layer 1
    Matrix n2;                       // n vector for layer 2
    Matrix s1;                       // s vector for layer 1
    Matrix s2;                       // s vector for layer 2 

    const char* af1{ "Sigmoid" };    //activation function layer 1
    const char* af2{ "Sigmoid" };    //activation function layer 2
    size_t hidden_layer_neurons{ 3 };//No of neurons in the hidden layer of the network
    double lr{ 0.01 };               //Learning rate for the training algorithm.
    size_t max_iters{ 1000 };        //Maximum iterations
    double min_loss{ 0.01 };         //Minimum test loss
    Dataset dataset;                 //Given dataset

public:                                                         //member functions
    NeuralNet(Dataset dataset, size_t hidden_layer_neurons, const char* f1 = "Sigmoid", const char* f2 = "Linear", double lr = 0.1, size_t max_iters = 10000, double min_loss = 0.01);   //constructor

    Matrix forwardPropagate(Matrix& input);                     //do the forward propagations process
    void backPropagate(Matrix& input, Matrix& target);          //do the backpropagation for a sample data
    double trainLoss();                                         //computes the average loss function on the train part
    double testLoss();                                          //computes the average loss function on the test part
    Result fit();                                               //do all the training process of the neural network
    void show();                                                //shows a description of the neural network
                                                                //setter and getter functions
    void setW1(Matrix& w);                                      //set w1 matrix
    void setW2(Matrix& w);                                      //set w2 matrix
    void setB1(Matrix& b);                                      //set b1 matrix
    void setB2(Matrix& b);                                      //set b2 matrix
    Matrix getW1();                                             //get w1 matrix
    Matrix getW2();                                             //get w2 matrix
    Matrix getB1();                                             //get b1 matrix
    Matrix getB2();                                             //get b2 matrix
  
    friend std::ostream& operator<< (std::ostream& out, NeuralNet& c);//difine operator <<
};

