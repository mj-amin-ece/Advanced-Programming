#include "legalCustomer.h"

LegalCustomer::LegalCustomer(const std::string& corrName, const std::string& compName) :Customer{corrName}
{
	companyName = compName;   //save copmany name
}

//operators
bool LegalCustomer::operator==(const Customer& in) const
{
	if (typeid(in) != typeid(LegalCustomer))
		return false;
	Customer* a{ const_cast<Customer*>(&in) };
	LegalCustomer* b = static_cast<LegalCustomer*>(a);
	return LegalCustomer::operator==(*b);
}

bool LegalCustomer::operator<(const Customer& in) const
{
	if (typeid(in) == typeid(LegalCustomer))
	{
		Customer* temp { const_cast<Customer*>(&in) };
		LegalCustomer* b = static_cast<LegalCustomer*>(temp);
		return LegalCustomer::operator<(*b);
	}
	return false;
}

bool LegalCustomer::operator==(const LegalCustomer& in) const
{
	if (name == in.name && companyName == in.companyName)
		return true;
	return false;
}

bool LegalCustomer::operator<(const LegalCustomer& in) const
{
	if (LegalCustomer::operator==(in))
		return false;
	
	if (name < in.name)
		return true;
	return false;
}

