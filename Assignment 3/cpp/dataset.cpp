#include "dataset.h"


Dataset::Dataset(Matrix inputs, Matrix targets, double percentage)                                                                    //constructor
{
	this->inputs = inputs;                                                                                                            //save input matrix
	this->targets = targets;                                                                                                          //save target matrix
	this->percentage = percentage;                                                                                                    //save percentage
	no_of_samples = inputs.getSize()[1];                                                                                              //save number of samples
	input_dim = inputs.getSize()[0];                                                                                                  //save input dimension
	target_dim = targets.getSize()[0];                                                                                                //save target dimension
	train_inputs = inputs.remain_matrix_until_col(static_cast<size_t>(no_of_samples * (percentage / 100)-1));                         //save train input matrix
	train_targets = targets.remain_matrix_until_col(static_cast<size_t>(no_of_samples * (percentage / 100) - 1));                     //save train target matrix
	test_inputs = inputs.remain_matrix_after_col(static_cast<size_t>(no_of_samples-no_of_samples * (1 - (percentage / 100))));        //save test input matrix
	test_targets = targets.remain_matrix_after_col(static_cast<size_t>(no_of_samples-no_of_samples * (1 - (percentage / 100))));      //save test target matrix
}

Dataset::Dataset()                                                                                  //default construvtos
{
	inputs = targets = train_inputs = train_targets = test_inputs = test_targets = Matrix{};        //save member varibles
	no_of_samples = input_dim = target_dim = 0;
}

size_t Dataset::getNoOfSamples()                          //get number of samples
{
	return size_t{no_of_samples};
}

size_t Dataset::getNoOfTrainSamples()                    //get number of train samples
{
	return size_t{train_inputs.getSize()[1]};          
}

size_t Dataset::getNoOfTestSamples()                     //get number of test samples
{
	return size_t{ test_inputs.getSize()[1] };
}

size_t Dataset::getInputDim()                            //get input dimension
{   
	return size_t{input_dim};
}

size_t Dataset::getTargetDim()                           //get target dimension
{
	return size_t{target_dim};
}

Matrix Dataset::getInputs()                              //get input matrix
{
	return Matrix{inputs};
}

Matrix Dataset::getTargets()                             //get target matrix
{
	return Matrix{targets};
}

Matrix Dataset::getTrainInputs()                         //get train inputs matrix
{
	return Matrix{train_inputs};
}

Matrix Dataset::getTrainTargets()                        //get train target matrix
{
	return Matrix{train_targets};
}

Matrix Dataset::getTestInputs()                          //get test inputs matrix
{
	return Matrix{test_inputs};
}

Matrix Dataset::getTestTargets()                         //get test targets matrix
{
	return Matrix{test_targets};
}

void Dataset::shuffle()                                               //rearranges the data samples
{
	srand(static_cast<unsigned>(time(NULL)));

	size_t counter{};                                  
	Matrix new_input{ std::vector<std::vector<double>>(inputs.getSize()[0], std::vector<double>(inputs.getSize()[1], -1000)) };
	Matrix new_target{ std::vector<std::vector<double>>(targets.getSize()[0], std::vector<double>(targets.getSize()[1], -1000)) };
	
	while (counter < no_of_samples)                                                     //count until all samples rearrange
	{
		size_t i{ rand() % no_of_samples };                                             //get a random column of  matrix
		size_t i_new{ rand() % no_of_samples };                                         //get a random column of  new matrix

		if (new_input[0][i_new]==-1000 && inputs[0][i]!=-1000)                          //check this colunm of new matrix is empty 
		{                                                                               //and check this sample of old matrix already use or not
			for (size_t row_input = 0; row_input < getInputDim(); row_input++)          //rearrange the element
				new_input[row_input][i_new] = inputs[row_input][i];
			for (size_t row_target = 0; row_target < getTargetDim(); row_target++)
				new_target[row_target][i_new] = targets[row_target][i];                                                        
			inputs[0][i] = -1000;                                                        //this show this column of old matrix uesed   
			counter++;                               
		} 
	}
	                                                                                     //save member variables of nee matrix
	inputs = new_input;                                                                  //save new input matrix
	targets = new_target;                                                                //save new target matrix
	train_inputs = inputs.remain_matrix_until_col(static_cast<size_t>(no_of_samples * (percentage / 100) - 1));                       //save train input matrix
	train_targets = targets.remain_matrix_until_col(static_cast<size_t>(no_of_samples * (percentage / 100) - 1));                     //save train target matrix
	test_inputs = inputs.remain_matrix_after_col(static_cast<size_t>(no_of_samples - no_of_samples * (1 - (percentage / 100))));      //save new test input matrix
	test_targets = targets.remain_matrix_after_col(static_cast<size_t>(no_of_samples - no_of_samples * (1 - (percentage / 100))));    //save new test target matrix
}

void Dataset::show()    //show some properties of the dataset
{
	std::cout << "Dataset:" << std::endl;
	std::cout << std::setw(20) << "No of samples: " << no_of_samples << std::endl;
	std::cout << std::setw(20) << "Train samples: " << getNoOfTrainSamples() << " samples" << std::endl;
	std::cout << std::setw(19) << "Test samples: " << getNoOfTestSamples() << " samples" << std::endl;
	std::cout << std::setw(23) << "Input dimensions: " << input_dim << std::endl;
	std::cout << std::setw(24) << "Target dimensions: " << target_dim << std::endl;
}

std::vector<Matrix> Dataset::operator[](size_t k)      //overload operator[] to return a reference to an object that represents the sample
{                                                      //and with itself has an appropriate operator[] to reference inputs matrix or target matrix
	return std::vector<Matrix>{ inputs.col(k),targets.col(k) };
}

Dataset Dataset::operator+(const Dataset& dataset)                                                //merge two datasets together
{
	return  Dataset{ inputs.attach(dataset.inputs),targets.attach(dataset.targets),percentage };  //return as a new dataset
}

std::ostream& operator<<(std::ostream& out,const Dataset& c)          //show some properties of the dataset
{
	out << "Dataset:" << std::endl;
	out << std::setw(20) << "No of samples: " << c.no_of_samples << std::endl;
	out << std::setw(20) << "Train samples: " << static_cast<size_t>(c.no_of_samples * (c.percentage / 100)) << " samples" << std::endl;
	out << std::setw(19) << "Test samples: " << c.no_of_samples - static_cast<size_t>(c.no_of_samples * (c.percentage / 100)) << " samples" << std::endl;
	out << std::setw(23) << "Input dimensions: " << c.input_dim << std::endl;
	out << std::setw(24) << "Target dimensions: " << c.target_dim << std::endl;
	
	return out;
}
