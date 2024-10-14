#include "realCustomer.h"

RealCustomer::RealCustomer(const std::string& name, long int nid) :Customer{name}  //constructor
{
	nationalID = nid;   //save national ID
}

long int RealCustomer::getNationalID(void)  //get national ID
{
	return nationalID;
}
  //operators
bool RealCustomer::operator==(const Customer& in) const
{
	if (typeid(in) != typeid(RealCustomer))
		return false;
	Customer* a{ const_cast<Customer*>(&in) };
	RealCustomer* b = static_cast<RealCustomer*>(a);
	return RealCustomer::operator==(*b);
}

bool RealCustomer::operator<(const Customer& in) const
{	
	if (typeid(in) == typeid(RealCustomer))
	{
		Customer* a{ const_cast<Customer*>(&in) };
		RealCustomer* b = static_cast<RealCustomer*>(a);
		return RealCustomer::operator<(*b);
	}
	return true;;
}

bool RealCustomer::operator==(const RealCustomer& in) const
{
	if (name == in.name && nationalID == in.nationalID)
		return true;
	return false;
}

bool RealCustomer::operator<(const RealCustomer& in) const
{
	if (RealCustomer::operator==(in))
		return false;
	else
		if (name < in.name)
			return true;
	return false;
}
