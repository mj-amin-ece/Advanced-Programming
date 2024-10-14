#include "neuralnet.h"


NeuralNet::NeuralNet(Dataset dataset, size_t hidden_layer_neurons, const char* f1, const char* f2, double lr, size_t max_iters, double min_loss)   //constructor
{
	this->dataset = dataset;                              //save dataset
	this->hidden_layer_neurons = hidden_layer_neurons;    //save number of neurons in the hidden layer of the network
	this->af1 = f1;                                       //save activation function layer 1
	this->af2 = f2;                                       //save activation function layer 2             
	this->lr = lr;                                        //save Learning rate
	this->max_iters = max_iters;                          //save Maximum iterations
	this->min_loss = min_loss;                            //save Minimum test loss
}

Matrix NeuralNet::forwardPropagate(Matrix& input)         //do the forward propagations process
{
	n1 = w1 * input + b1;                                 //claculate matrix n1
	std::string acf1{ af1 };                              //activation function layer 1
	std::string acf2{ af2 };                              //activation function layer 2

	if (acf1 == "Sigmoid")                                //check activatin function layer 1
		a1 = sigmoid(n1);                                 //calculate matrix a1                 
	else if (acf1 == "Linear")
		a1 = linear(n1); 
	else          
	{
		std::cout << " inavalid activation function layer 1" << std::endl;
		return Matrix{};
	}

	n2 = w2 * a1 + b2;                                   //claculate matrix n2
	
	if (acf2 == "Sigmoid")                               //check activatin function layer 2
		a2 = sigmoid(n2);                                //calculate matrix a2 
	else if (acf2 == "Linear")
		a2 = linear(n2);
	else
	{
		std::cout << " inavalid activation function layer 2" << std::endl;
		return Matrix{};
	}

	return a2;                                          //return matrix a2
}

void NeuralNet::backPropagate(Matrix& input, Matrix& target)            //do the backpropagation for a sample data
{
	Matrix F1{hidden_layer_neurons,hidden_layer_neurons,false};         //matrix F1
	Matrix F2{ dataset.getTargetDim(),dataset.getTargetDim(),false };   //matrix F2
	std::string acf1{ af1 };                                            //activation function layer 1
	std::string acf2{ af2 };                                            //activation function layer 2

	if (acf1 == "Sigmoid")                                               //check activatin function layer 1
		for (size_t i = 0; i < F1.getSize()[0]; i++)
			F1[i][i] = d_sigmoid(n1[i][0]);                             //calculate drivative 
	if(acf1=="Linear")
		for (size_t i = 0; i < F1.getSize()[0]; i++)
			F1[i][i] = d_linear(n1[i][0]);
	if (acf2 == "Sigmoid")                                               //check activatin function layer 2
		for (size_t i = 0; i < F2.getSize()[0]; i++)
			F2[i][i] = d_sigmoid(n2[i][0]);                             //calculate drivative 
	if (acf2 == "Linear")
		for (size_t i = 0; i < F2.getSize()[0]; i++)
			F2[i][i] = d_linear(n2[i][0]);

	s2= -2 * F2 * (target - a2) ;                                      //calculate matrix s2
	s1 = F1 * (w2.T()) * s2;                                           //calculate matrix s1
	w1 = w1 - lr * s1 * (input.T());                                   //updata matrix w1
	w2 = w2 - lr * s2 * (a1.T());                                      //updata matrix w2
	b1 = b1 - lr * s1;                                                 //updata matrix b1
	b2 = b2 - lr * s2;                                                 //updata matrix b2
}

double NeuralNet::trainLoss()                                         //computes the average loss function on the train part
{
	double loss{};                                                    //loss

	for (size_t i = 0; i < dataset.getNoOfTrainSamples(); i++)        //each sample
	{
		Matrix input_f{ dataset.getTrainInputs().col(i) };            //matrix inputs each sample

		for (size_t j = 0; j < dataset.getTargetDim(); j++)           //calculate loss
			loss += (dataset.getTrainTargets().T()[i][j] - forwardPropagate(input_f)[j][0]) * (dataset.getTrainTargets().T()[i][j] - forwardPropagate(input_f)[j][0]);
	}

	return loss / dataset.getNoOfTrainSamples();                      //return loss
}

double NeuralNet::testLoss()                                           //computes the average loss function on the test part
{
	double loss{};                                                     //loss

	for (size_t i = 0; i < dataset.getNoOfTestSamples(); i++)          //each sample
	{
		Matrix input_f{ dataset.getTestInputs().col(i) };              //matrix inputs each sample
		
		for (size_t j = 0; j < dataset.getTargetDim(); j++)            //calculate loss
			loss += (dataset.getTestTargets().T()[i][j] - forwardPropagate(input_f)[j][0]) * (dataset.getTestTargets().T()[i][j] - forwardPropagate(input_f)[j][0]);
	}

	return loss / dataset.getNoOfTestSamples();                        //return loss
}

Result NeuralNet::fit()                                                                     //do all the training process of the neural network
{
	size_t iteration{};                                                                     //to count iteration
	w1 = Matrix{ hidden_layer_neurons,dataset.getInputDim(),false };                        //initialize matrix w1
	w2 = Matrix{ dataset.getTargetDim(),hidden_layer_neurons,false };                       //initialize matrix w2
	b1 = Matrix{ hidden_layer_neurons,1,true };                                             //initialize matrix b1
	b2 = Matrix{ dataset.getTargetDim(),1,true };                                           //initialize matrix b2
	srand(static_cast<unsigned>(time(NULL)));

	while (iteration < max_iters)
	{
		size_t no_sample_random{ rand() % dataset.getNoOfTrainSamples() };                  //get a random sample
		Matrix sample_random_input{ dataset.getTrainInputs().col(no_sample_random) };       //get matrix inputs sample
		Matrix sample_random_output{ dataset.getTrainTargets().col(no_sample_random) };     //get matrix targets sample
		Matrix forwad_pro{ forwardPropagate(sample_random_input) };                         //do forward propagate
		backPropagate(sample_random_input, sample_random_output);                           //do backward propagate
		iteration++;                                                                       
		if (trainLoss() < min_loss)                                                         //check convergence
			break;
	} 
	
	return Result{trainLoss(),testLoss(),hidden_layer_neurons,lr,iteration,af1,af2};        //return result
}

void NeuralNet::show()                                                                      //shows a description of the neural network
{
	std::cout << "Neural Network:" << std::endl;
	std::cout << std::setw(26) << "No of hidden neurons: " << hidden_layer_neurons << std::endl;
	std::cout << std::setw(21) << "Input dimension: " << dataset.getInputDim() << std::endl;
	std::cout << std::setw(22) << "Output dimension: " << dataset.getTargetDim() << std::endl;
	std::cout << std::setw(32) << "Layer1 activation function: " << af1 << std::endl;
	std::cout << std::setw(32) << "Layer2 activation function: " << af2 << std::endl;
}

void NeuralNet::setW1(Matrix& w)         //set w1 matrix
{
	w1 = w;
}

void NeuralNet::setW2(Matrix& w)        //set w2 matrix
{
	w2 = w;
}

void NeuralNet::setB1(Matrix& b)        //set b1 matrix
{
	b1 = b;
}

void NeuralNet::setB2(Matrix& b)        //set b2 matrix
{
	b2 = b;
}

Matrix NeuralNet::getW1()               //get w1 matrix
{
	return w1;
}

Matrix NeuralNet::getW2()              //get w2 matrix
{
	return w2;
}

Matrix NeuralNet::getB1()              //get b1 matrix
{
	return b1;
}

Matrix NeuralNet::getB2()             //get b2 matrix
{
	return b2;
}

std::ostream& operator<<(std::ostream& out, NeuralNet& c)           //shows a description of the neural network
{
	out << "Neural Network:" << std::endl;
	out << std::setw(26) << "No of hidden neurons: " << c.hidden_layer_neurons << std::endl;
	out << std::setw(21) << "Input dimension: " << c.dataset.getInputDim() << std::endl;
	out << std::setw(22) << "Output dimension: " << c.dataset.getTargetDim() << std::endl;
	out << std::setw(32) << "Layer1 activation function: " << c.af1 << std::endl;
	out << std::setw(32) << "Layer2 activation function: " << c.af2 << std::endl;

	return out;
}

Matrix sigmoid(Matrix x)                               //activation function sigmoid
{
	for (size_t i = 0; i < x.getSize()[0]; i++)        //row
		for (size_t j = 0; j < x.getSize()[1]; j++)    //column
			x[i][j] = 1 / (1 + exp(-x[i][j]));         //claculate elements
	return x;                                          //return  output matrix
}
 
Matrix linear(Matrix x)                                //activation function linear
{
	return x;                                          //return  output matrix
}

double d_sigmoid(double x)                             //drivative function sigmoid
{
	return (1/(1+exp(-x)))*(1- (1 / (1 + exp(-x))));   //return drivative
}

double d_linear(double x)                              //drivative function linear
{
	return 1;                                          //return drivative
}

Matrix operator*(double a, Matrix B)                   //opreator multipluy scaler to matrix
{
	for (size_t i = 0; i < B.getSize()[0]; i++)        //row
		for (size_t j = 0; j < B.getSize()[1]; j++)    //column
			B[i][j] *= a;                              //claculate each element
	return B;                                          //return matrix
}

