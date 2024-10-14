#pragma once
#include<fstream>
#include<string>
#include <memory>
#include"apqueue.h"
#include"normalstudent.h"
#include"exponentialstudent.h"

std::vector<std::unique_ptr <Student>> getData(const char* filename);   //get data from .csv file
