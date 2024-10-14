#include"aphw3.h"

Dataset loadFuncDataset(const char* filename)                                     //gets a csv filenameand turn it into a dataset
{
	Matrix data{};
	data.load(filename);                                                          //load csv file

	return Dataset{ data.del_last_row(),data.re_row(data.getSize()[0] - 1) };     //return dataset
}

std::vector<Result> testNeuralNets(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr, size_t max_iters, const char* af1, const char* af2)  //This function generates a bunch of neural networks with a given dataset
{
	std::vector<Result> result_vector(hidden_neurons.size());                    //to store vector of results neural networks

	for (size_t i = 0; i < hidden_neurons.size(); i++)                           //each neural networks
	{
		NeuralNet temp{ dataset,hidden_neurons[i],af1,af2,lr,max_iters };        //create each neural networks
		result_vector[i] = temp.fit();                                           //process each neural netwok
	}
	
	return result_vector;                                                        //return vector of results
}

Result findBestNeuralNet(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr, size_t max_iters, const char* af1, const char* af2)  //generate a bunch of neural networks and then return the best result
{
	std::vector<Result> result_vector{ testNeuralNets(dataset,hidden_neurons,lr,max_iters,af1,af2) };  //to store vector of results neural networks
	Result min{ result_vector[0] };                                                                    //initialize min result

	for (size_t i = 1; i < result_vector.size(); i++)                                                  //each neural networks
	{
		if (min > result_vector[i])                                                                    //check for min results
			min = result_vector[i];
	}

	return min;                                                                                        //return min result
}

void estimateFunction(const char* filename, size_t hidden_neurons_no)
{
	Dataset data{ loadFuncDataset(filename) };            //gets a csv filenameand turn it into a dataset
	NeuralNet net_data{ data,hidden_neurons_no };         //create neural network
	net_data.fit();                                       //train neural netwotk
	                                                      //show the estimate numbers
	std::cout <<std::setw(10)<< "No" << std::setw(18) << "Target" << std::setw(22) << "Estimated" << std::endl;
	for (size_t i = 0; i < 10; i++)
		std::cout << "------";
	std::cout << std::endl;
	
	for (size_t i = 0; i < data.getNoOfSamples(); i++)    //show each target and estimate
	{
		Matrix input_matrix{ data.getInputs().col(i) };   //get inputs matrix of each sample
		std::cout << "        ";
		std::cout<<std::setiosflags(std::ios::left)<<std::setw(14)<< i + 1 << std::setw(19) << data.getTargets()[0][i];
		std::cout<< net_data.forwardPropagate(input_matrix)[0][0] << std::endl;
	}
}
