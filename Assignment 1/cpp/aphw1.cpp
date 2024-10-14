#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>


std::vector<std::vector<double>> getData(const char* ch)
{
	std::ifstream in_file{ ch };
	double data{};
	std::string temp{};
	std::vector<std::vector<double>> data_vector;

	for (size_t i = 0; i < 234; i++)
	{
		std::vector<double> row{ 1 };

		for (size_t j = 0; j < 6; j++)
		{
			std::getline(in_file, temp, ',');
			data = std::stod(temp);
			if (j == 2 || j == 3)
				data = data / 100.;
			row.push_back(data);
		}
		in_file >> temp;
		data = std::stod(temp);
		row.push_back(data);
		data_vector.push_back(row);
	}
	return data_vector;
}

void displayDataset(std::vector <std::vector <double >> v)
{
	std::cout << "Bias" << std::setw(17) << "Class" << std::setw(19) << "TA" << std::setw(23) << "Coding" << std::setw(21) << "Studying" << std::setw(20) << "Back ground";
	std::cout << std::setw(17) << "Mind" << std::setw(20) << "Grade" << std::endl;
	for (size_t i = 0; i < 36 ; i++)
		std::cout << "****";
	std::cout << std::endl;
	
	for (size_t i = 0; i < 234; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (j == 3 || j == 4)
				v[i][j] = 100 * v[i][j];
			if (j == 7)
				std::cout << v[i][j] << std::endl;
			else
				std::cout <<v[i][j]  << std::setw(20);
		}
	}
}

double grade(std::vector<double> w, std::vector<double> x)
{
	double grade_student{};

	for (size_t i = 0; i < 7; i++)
		grade_student += x[i] * w[i];

	return grade_student;
}

double J(std::vector<double> w, std::vector<std::vector<double>> data )
{
	double cost{};

	for (size_t i = 0; i < 234; i++)
	{
		std::vector<double> x{};

		for (size_t j = 0; j < 7; j++)
			x.push_back(data[i][j]);

		cost += (grade(w, x) - data[i][7])*(grade(w, x) - data[i][7]);
	}

	return cost/(2*234.);
}

std::vector<double> train(std::vector<std::vector<double>> data, std::vector<double> w, double alpha, size_t max_iters, double min_cost, bool verbose)
{
	std::vector<double> w_i{ w };
	
	for (size_t step{}; step < max_iters; step++)
	{
		std::vector<double> derivative(7,0);

		for (size_t i = 0; i <234 ; i++)
		{
			std::vector<double> x{};
			for (size_t j = 0; j < 7; j++)
			{
				x.push_back(data[i][j]);
			}
			for (size_t j = 0; j < 7; j++)
				derivative[j] += ((grade(w_i, x) - data[i][7]) * x[j]);
		}
		if (verbose == 1)
			std::cout << "iteration " << std::setw(6) << step + 1 << " : the last value of the cost function is : " << std::setiosflags(std::ios::right)<<std::setw(13)  << J(w_i, data) << std::endl;
		for (size_t i{}; i < 7; i++)
			w_i[i] = w_i[i] - (alpha * (derivative[i])/234.);
		if (verbose == 1)
			std::cout << "iteration " << std::setw(6) << step + 1 << " : the current value of the cost function is : " << std::setw(10) << J(w_i, data) << std::endl;
		if(verbose==1)
			std::cout << std::endl;
		if (J(w_i, data) < min_cost)
			break;
	}
	
	return w_i;
}

void displayOutput(std::vector<std::vector<double>> data,std::vector<double> w)
{
	std::cout << "  No" << std::setw(25) << "Real Grade" << std::setw(23) << "Estimated Grade" << std::endl;
	for (size_t i = 0; i < 28; i++)
		std::cout << "**";
	std::cout << std::endl;

	for (size_t i = 1; i <= 234; i++)
	{
		std::vector<double> x{};
		for (size_t j = 0; j < 7; j++)
		{
			x.push_back(data[i-1][j]);
		}
		std::cout <<std::setw(4)  << i << std::setw(20)<< data[i-1][7] << std::setw(20) << grade(w, x)<<std::endl;
	}
}

void save(std::vector<double> w, const char* name)
{
	std::ofstream out_file{ name };

	for (size_t i = 0; i < w.size(); i++)
		out_file << w[i]<<",";
	out_file.close();
}

std::vector<double> load(const char* name)
{
	std::ifstream in_file{ name };
	std::vector<double> w{};
	double temp{};
	char ch;

	for (size_t i = 0; i < 7; i++)
	{
		in_file >> temp>>ch ;
		w.push_back(temp);
	}
	in_file.close();

	return w;
}

void predict(std::vector<double> w)
{
	std::vector<double> x(7,0);
	bool flag{ true };
	std::string error{ "your number must be Between 0 and 1 " };
	std::string error1{ "your number must be positive " };
	
	x[0] = 1;

	try{
		std::cout << "please enter your mark factors" << std::endl;
		std::cout << "mark of Attention in the class (Between 0 and 1) : ";
		std::cin >> x[1];
		if (x[1] <= 1 && x[1] >= 0)
			flag = true;
		else
			throw std::invalid_argument(error);
		std::cout << std::endl << "mark of Attention in the TA class (Between 0 and 1) : ";

		std::cin >> x[2];
		if (x[2] <= 1 && x[2] >= 0)
			flag = true;
		else
			throw std::invalid_argument(error);

		std::cout << std::endl << "Hours of coding and practicing in the week : ";
		std::cin >> x[3];
		if (x[3] >= 0)
			flag = true;
		else
			throw std::invalid_argument(error1);
		x[3] = x[3] / 100.;

		std::cout << std::endl << "Hours of studing and reading books in the week : ";
		std::cin >> x[4];
		if (x[4] >= 0)
			flag = true;
		else
			throw std::invalid_argument(error1);
		x[4] = x[4] / 100.;

		std::cout << std::endl << "mark of Previous background (Between 0 and 1) : ";
		std::cin >> x[5];
		if (x[5] <= 1 && x[5] >= 0)
			flag = true;
		else
			throw std::invalid_argument(error);

		std::cout << std::endl << "mark of Talent(Between 0 and 1) : ";
		std::cin >> x[6];
		if (x[6] <= 1 && x[6] >= 0)
			flag = true;
		else
			throw std::invalid_argument(error);
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what()<<std::endl;
		flag = false;
	}
	if (flag)
	{
		if (grade(w, x) > 20)
			std::cout << "your grade is : 20 " << std::endl;
		else
			std::cout << "your grade is : " << grade(w, x) << std::endl;
	}
}

