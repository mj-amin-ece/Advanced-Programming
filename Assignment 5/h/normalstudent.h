#pragma once
#include "student.h"

class NormalStudent : public Student
{
private:
	double mean;   //mean
	double std;    //std 
public:
	NormalStudent(std::string name, double mean = 12, double std = 2);  //constructor
	NormalStudent();   //default constructor

	double pdf(double x);                    //pdf function
	double integrator(double a, double b, double step_size = 0.001);  //integrator function
	double between(double a, double b);      //probablity between a , b
	double operator()(double x);             //operator() return pdf(x)
	double operator()(double a, double b);   //operator() return between(a,b)
	std::string getName();                   //get name
};

