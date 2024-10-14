#pragma once

#include<iostream>
#include<iomanip>


class Result
{  
private:                              //member variable 
    double train_loss;                //average loss function on the train part
    double test_loss;                 //average loss function on the test part
    size_t no_of_hidden_neurons;      //No of neurons in the hidden layer of the network
    double lr{};                      //Learning rate for the training algorithm.
    size_t iters{};                   //iterations
    const char* af1;                  //activation function layer 1
    const char* af2;                  //activation function layer 2

public:                               //member functions
    Result(double train_loss, double test_loss, size_t no_of_hidden_neurons, double lr = 0.01, size_t iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear");  //constructor
    explicit Result( double test_loss);                                  //explicit keyword makes this constructor ineligible for implicit conversions
    Result();                                                            //default constructor

    double getTestLoss();                                                //get loss on the test part
    void show();                                                         //shows a description of the result object
                                                                         //operator
    bool operator<(const Result&) const;                                 //define operator <
    bool operator==(const Result&) const;                                //define operator ==
    friend std::ostream& operator<< (std::ostream& out, const Result& c);//difine operator <<
};

