#pragma once

#include<iostream>
#include<iomanip>
#include<utility>
#include"Matrix.h"
#include"dataset.h"
#include"neuralnet.h"
#include"result.h"


using namespace std::rel_ops;


Dataset loadFuncDataset(const char* filename);                                                                                                                                                  //gets a csv filenameand turn it into a dataset
std::vector<Result> testNeuralNets(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr = 0.01, size_t max_iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear"); //This function generates a bunch of neural networks with a given dataset
Result findBestNeuralNet(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr = 0.01, size_t max_iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear");           //generate a bunch of neural networks and then return the best result
void estimateFunction(const char* filename, size_t hidden_neurons_no);                                                                                                                          //generate neural networks and estimate