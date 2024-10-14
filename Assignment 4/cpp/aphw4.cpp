#include"aphw4.h"


std::vector<Student> getData(const char* filename) //read .csv file and get students
{
	std::ifstream input_file{ filename };   //read .csv file
	static std::vector<Student> output{};          //for store students

	while (!input_file.eof())               // while until end of file
	{
		std::string student{};      //for store each student(line of data)
		std::string data{};         //for store each data of student in a row
		Student input_student{};            //for save student in each row
		size_t j{};
		std::getline(input_file, student);     //store each student(line) 

		if (static_cast<int>(student[0] == 0))  //if line is empty break from loop
			break;

		for (size_t i = 0; i < student.length(); i++)  //to get data from a line
		{
			if (student[i] != ',')    
				data += student[i];
			else
			{
				if (j == 0)    //set id
					input_student.setID(static_cast<long>(std::stod(data)));
				else if (j == 1)   //set homework
					input_student.setHomework(std::stod(data));
				else if (j == 2)  //set midterm project
					input_student.setMidtermProject(std::stod(data));
				else if (j == 3)   //set midterm exam
					input_student.setMidtermExam(std::stod(data));

				data = "";
				j++;
			}
		}
		input_student.setParty(std::stod(data)); //set party
		output.push_back(input_student);   //save student
	}
	input_file.close();

	return output;

}

void show(std::vector<Student> student)     //show students
{
	std::cout << std::setw(20) << "N" << std::setw(20) << "ID" << std::setw(20) << "Homework" << std::setw(20);
	std::cout << "MidProject" << std::setw(20) << "MidExam" << std::setw(20) << "Party" << std::setw(20);
	std::cout << "Value" << std::endl;

	for (size_t i = 0; i < student.size(); i++)
	{
		std::cout << std::setw(20) << i + 1 << std::setw(20) << student[i].getID() << std::setw(20) << student[i].getHomework();
		std::cout << std::setw(20) << student[i].getMidtermProject() << std::setw(20) << student[i].getMidtermExam();
		std::cout << std::setw(20) << student[i].getParty() << std::setw(20) << student[i].value() << std::endl;
	}
}

void show(const APDS& ap)       //shows properties of an APDS object
{
	ap.show();
}
