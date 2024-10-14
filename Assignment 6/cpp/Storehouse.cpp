#include "Storehouse.h"

Storehouse::Storehouse(const std::string& name)   //constructor
{
	storeName = name;   //save name storehouse
}

void Storehouse::newCustomer(std::shared_ptr<Customer> newC)  //add new customer
{
	bool flag{ false };   //to show new customer added

	for (auto it = theCustomers.begin(); it != theCustomers.end(); it++)  //cheack for repeat customer
	{
		if ((*(*it)) == *newC)   //if find repeated customer
		{
			size_t size{ (*newC).getassets().size() };
			for (size_t i{}; i < size; i++)  //import all new goods
				(*(*it)).importNewGoods((*newC).getassets()[i]);
			flag = true;  //show add new customer
			break;
		}
	}
	if(!flag)  //if not added new customer yet add it
		theCustomers.insert(newC);
}

std::string Storehouse::printCustomers(void) const   //print detail of all customer
{
	std::ostringstream print_InFo{};
	for (auto it = theCustomers.begin(); it != theCustomers.end(); it++)
	{
		if (typeid(LegalCustomer) == typeid(*(*it)))
			print_InFo << "Legal : ";
		else if (typeid(RealCustomer) == typeid(*(*it)))
			print_InFo << "Real : ";
		print_InFo << (*it).get()->printBasicInfo() << std::endl;
	}
	std::cout << print_InFo.str() << std::endl;

	return print_InFo.str();

}
