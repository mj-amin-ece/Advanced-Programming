#include "exponentialstudent.h"

ExponentialStudent::ExponentialStudent(std::string name, double lamda)  //constructor
{
	this->lambda = lamda;   //save lambda
	this->name = name;      //save name
}

ExponentialStudent::ExponentialStudent()   //copy constructor
{
	lambda = 0.07;
	name = {"mj amin"};   
}

double ExponentialStudent::pdf(double x)   //pdf function
{
	return (lambda)*exp(-lambda * x);
}

double ExponentialStudent::integrator(double a, double b, double step_size)  //integtator
{
	double sum{};
	double temp{ a };  //start from a

	for (size_t step{}; step <= (b - a) / step_size; step++)
	{
		if (step == 0 || step == (b - a) / step_size) 
			sum += pdf(temp) / 2;
		else
			sum += pdf(temp);
		temp += step_size;
	}

	return step_size * sum;   //retrnu integrator (a,b)
}

double ExponentialStudent::between(double a, double b)    //probablity between a , b
{
	return integrator(a,b);
}

double ExponentialStudent::operator()(double x)             //operator() retuen pdf(x)
{
	return pdf(x);
}

double ExponentialStudent::operator()(double a, double b)   //operator()  return between(a,b)
{
	return between(a,b);
}

std::string ExponentialStudent::getName()                   //get name
{
	return name;
}
