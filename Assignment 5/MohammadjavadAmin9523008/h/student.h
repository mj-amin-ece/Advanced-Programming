#pragma once
#include<string>
#include<cmath>

class Student
{
protected:
	std::string name{"MJ amin"};   //name student
public:
	virtual double pdf(double x)=0;                    //pdf function
	virtual double integrator(double a, double b, double step_size = 0.001) = 0;  //integrator
	virtual double between(double a, double b) = 0;   //probablity between a , b
	virtual std::string getName() = 0;                //get name
};

