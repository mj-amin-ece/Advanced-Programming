#pragma once
#include<fstream>
#include<string>
#include"student.h"
#include"apds.h"


std::vector<Student> getData(const char* filename);  //read .csv file and get students
void show(std::vector<Student> student);             //show students
void show(const APDS& ap);                           //shows properties of an APDS object
