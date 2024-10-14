#include "result.h"


Result::Result(double train_loss, double test_loss, size_t no_of_hidden_neurons, double lr, size_t iters, const char* af1, const char* af2)
{
	this->train_loss = train_loss;                                    //save train loss 
	this->test_loss = test_loss;                                      //save test loss
	this->no_of_hidden_neurons = no_of_hidden_neurons;                //save Number of neurons in the hidden layer   
	this->lr = lr;                                                    //save Learning rate
	this->iters = iters;                                              //save iterations
	this->af1 = af1;                                                  //save activation function layer 1
	this->af2 = af2;                                                  //save activation function layer 2
}

 Result::Result( double test_loss) 
{
	this->test_loss = test_loss;                                      //save train loss 
	train_loss = -1;                                                  //save test loss
	no_of_hidden_neurons = 0;                                         //save Number of neurons in the hidden layer
	lr = 0.01;                                                        //save Learning rate
	iters = 10000;                                                    //save iterations
	af1 = "Sigmoid";                                                  //save activation function layer 1
	af2 = "Linear";                                                   //save activation function layer 2
}

 Result::Result()                                                      //default constructor
 {
	 test_loss = 0;                                                    //save train loss 
	 train_loss = -1;                                                  //save test loss
	 no_of_hidden_neurons = 0;                                         //save Number of neurons in the hidden layer
	 lr = 0.01;                                                        //save Learning rate
	 iters = 10000;                                                    //save iterations
	 af1 = "Sigmoid";                                                  //save activation function layer 1
	 af2 = "Linear";                                                   //save activation function layer 2
 }

double Result::getTestLoss()                                          //get loss on the test part
{
	return test_loss;
}

void Result::show()                                                   //shows a description of the result object
{
	std::cout << "Result:" << std::endl;
	std::cout << std::setw(16) << "Train loss: " << train_loss << std::endl;
	std::cout << std::setw(15) << "Test loss: " << test_loss << std::endl;
	std::cout << std::setw(26) << "No of hidden neurons: " << no_of_hidden_neurons << std::endl;
	std::cout << std::setw(32) << "Layer1 activation function: " << af1 << std::endl;
	std::cout << std::setw(32) << "Layer2 activation function: " << af2 << std::endl;
}

bool Result::operator<(const Result& A) const         //define operator <
{
	if (test_loss < A.test_loss)                      //compare test loss
		return true;
	else
		return false;
}

bool Result::operator==(const Result& A) const       //define operator ==
{
	if (test_loss == A.test_loss)                    //compare test loss
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& out, const Result& c)  //difine operator <<
{                                                             //shows a description of the result object
	out << "Result:" << std::endl;
	out << std::setw(16) << "Train loss: " << c.train_loss << std::endl;
	out << std::setw(15) << "Test loss: " << c.test_loss << std::endl;
	out << std::setw(26) << "No of hidden neurons: " << c.no_of_hidden_neurons << std::endl;
	out << std::setw(32) << "Layer1 activation function: " << c.af1 << std::endl;
	out << std::setw(32) << "Layer2 activation function: " << c.af2 << std::endl;

	return out;
}