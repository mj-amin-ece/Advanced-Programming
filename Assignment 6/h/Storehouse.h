#ifndef __STOREHOUSE_HEADER__
#define __STOREHOUSE_HEADER__
#include <vector>
#include "basicGoods.h"
#include <set>
#include "customer.h"
#include <string>
#include"legalCustomer.h"
#include"realCustomer.h"

class Storehouse
{
private:
	std::string storeName;   //store name
	std::set < std::shared_ptr<Customer>, Shared_less<Customer>> theCustomers;  //all customer

public:
	explicit Storehouse(const std::string& name);   //constructor
	Storehouse() = default;   //default constructor

	void newCustomer(std::shared_ptr<Customer> newC );   //add new customer
	std::string printCustomers(void) const;     //print detail of all customer
};

#endif // __STOREHOUSE_HEADER__