#include "student.h"

Student::Student(long id, double hw, double mid_proj, double mid_exam, double party)   //constructor
{
	this->id = id;                          //save student's id
	homework = hw;                          //save student's homeworks grade
	midterm_project = mid_proj;             //save student's midterm project grade
	midterm_exam = mid_exam;                //save student's midterm exam grade
	this->party = party;                    //save amont of party
}

void Student::setID(long id)               //set student's id
{
	this->id = id;
}

long Student::getID()                     //get student's id
{
	return id;
}

void Student::setHomework(double hw)      //set student's homeworks grade
{
	homework = hw;
}

double Student::getHomework()             //get student's homework grade
{
	return homework;
}

void Student::setMidtermProject(double project)//set student's midterm project
{
	midterm_project = project;
}

double Student::getMidtermProject()      //get student's midterm project
{
	return midterm_project;
}

void Student::setMidtermExam(double exam)//set student's midterm exam
{
	midterm_exam = exam;
}

double Student::getMidtermExam()       //get student's midterm exam
{
	return midterm_exam;
}

void Student::setParty(double party)   //set amount of party
{
	this->party = party;
}

double Student::getParty()             //get amount of party 
{
	return party;
}

double Student::value()             //likelihood of a student to take the exam
{
	return -(homework + midterm_project + midterm_exam) / 3 + party; //calculate and return value
}

void Student::show()                //display informations of a student
{
	std::cout << "Student ID:" << std::setw(10) << id << std::setw(20) << "Homework:" << std::setw(5) << homework;
	std::cout << std::setw(20) << "Midterm project:" << std::setw(5) << midterm_project << std::setw(17);
	std::cout << "Midterm exam:" << std::setw(5) << midterm_exam << std::setw(10) << "Party:" << std::setw(5) << party;
	std::cout << std::setw(10) << "Value:" << std::setw(5) << value() << std::endl;
}

std::ostream& operator<<(std::ostream& os, Student& student)  //define operator <<
{                                                             //display informations of a student
	os << "Student ID:" << std::setw(10) << student.id << std::setw(20) << "Homework:" << std::setw(5) << student.homework;
	os << std::setw(20) << "Midterm project:" << std::setw(5) << student.midterm_project << std::setw(17);
	os << "Midterm exam:" << std::setw(5) << student.midterm_exam << std::setw(10) << "Party:" << std::setw(5) << student.party;
	os << std::setw(10) << "Value:" << std::setw(5) << student.value() << std::endl;

	return os;
}
