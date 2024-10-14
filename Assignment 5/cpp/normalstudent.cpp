#include "normalstudent.h"

NormalStudent::NormalStudent(std::string name, double mean, double std) //constructor
{
	this->mean = mean;   //save mean
	this->std = std;     //save std
	this->name = name;   //save name
}

NormalStudent::NormalStudent()  //default constructor
{
	mean = 12;                  //save mean
	std = 2;                    //save std
	name = { "mj amin" };       //save name
}

double NormalStudent::pdf(double x) //pdf function
{
	const double pi{ 3.14159 };
	
	return (1 / (std::sqrt(2 * pi) * std)) * exp(-(1 / (2 * std * std)) * (x - mean) * (x - mean));
}

double NormalStudent::integrator(double a, double b, double step_size)  //integtator
{
	double sum{};
	double temp{ a };                                   //start from a

	for (size_t step{}; step <= (b - a) / step_size; step ++)
	{
		if (step == 0 || step == (b - a) / step_size)
			sum += pdf(temp) / 2;
		else
			sum += pdf(temp);
		temp += step_size;
	}

	return step_size*sum;                               //retrnu integrator (a,b)
}

double NormalStudent::between(double a, double b)       //probablity between a , b
{
	return integrator(a,b);
}

double NormalStudent::operator()(double x)              //operator() retuen pdf(x)
{
	return pdf(x);
}

double NormalStudent::operator()(double a, double b)    //operator()  return between(a,b)
{
	return between(a,b);
}

std::string NormalStudent::getName()                    //get name
{
	return name;
}
