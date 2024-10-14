#include"apmidterm.h"

std::vector<std::unique_ptr <Student>> getData(const char* filename)    //get data from .csv file
{
	std::vector<std::unique_ptr <Student>> output{};  //for store students
	std::ifstream input_file{ filename };             //read .csv file

	while (!input_file.eof())                         //while until end of file
	{
		std::string student{};                        //for store each student(line of data)
		std::string data{};                           //for store each data of student in a row
		std::unique_ptr <Student> input_student{};    //for save student in each row
		size_t j{};

		std::getline(input_file, student);            //store each student(line) 

		if (static_cast<int>(student[0] == 0))        //if line is empty break from loop
			break;
		
		std::string name;       //name student
		double x{}, y{};
		bool normal{ false };   //show it's normal or not

		for (size_t i{}; i < student.size(); i++)   //to get data from a line
		{
			if (student[i] != ',')
				data += student[i];
			else
			{
				if (j == 0)          //set name
					name = data;
				else if (j == 1)     //set a
				{
					x = std::stod(data);
					normal = true;   //it's normal Steudent
				}
				data = "";
				j++;
			}
		}

		y = std::stod(data);    //set b

		if (normal)
		{
			NormalStudent temp{ name,x,y };        //save this normal Student
			output.push_back(std::make_unique<NormalStudent>(temp));
		}
		else
		{
			ExponentialStudent temp{ name,y };    //save this exponentialStudent
			output.push_back(std::make_unique<ExponentialStudent>(temp));
		}
	}

	return output;
}