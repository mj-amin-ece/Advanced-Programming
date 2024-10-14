#pragma once
#include<iostream>
#include<iomanip>

class Student
{
private:                     //member variables
	long id{};               //student's id
	double homework{};       //student's homeworks grade
	double midterm_project{};//student's midterm project grade
	double midterm_exam{};   //student's midterm exam grade
	double party{};          //student's amount of friendship with the TAs
public:                      //member functions
	Student(long id, double hw, double mid_proj, double mid_exam, double party = 50);   //constructor
	Student() = default;                                                       //default constructor

	void setID(long id);                                                       //set student's id
	long getID();                                                              //get student's id
	void setHomework(double hw);                                               //set student's homeworks grade
	double getHomework();                                                      //get student's homework grade
	void setMidtermProject(double project);                                    //set student's midterm project
	double getMidtermProject();                                                //get student's midterm project
	void setMidtermExam(double exam);                                          //set student's midterm exam
	double getMidtermExam();                                                   //get student's midterm exam
	void setParty(double party);                                               //set amount of party
	double getParty();                                                         //get amount of party 
	double value();                                                            //likelihood of a student to take the exam
	void show();                                                               //display informations of a student
				                                                               //operator
	friend std::ostream& operator<<(std::ostream& os, Student& student);       //display informations of a student
};

