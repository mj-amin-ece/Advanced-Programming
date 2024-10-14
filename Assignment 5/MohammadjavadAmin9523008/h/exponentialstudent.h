#pragma once
#include"student.h"

class ExponentialStudent : public Student
{
private:
	double lambda;      //lambda
public:
	ExponentialStudent(std::string name, double lambda = 0.07);  //constructor
	ExponentialStudent();                                        //defual constructor

	double pdf(double x);                                        //pdf function
	double integrator(double a, double b, double step_size = 0.001);  //integrator function
	double between(double a, double b);                          //probablity between a , b
	double operator()(double x);                                 //operator() retuen pdf(x)
	double operator()(double a, double b);                       //operator()  return between(a,b)
	std::string getName();                                       //get name

};

