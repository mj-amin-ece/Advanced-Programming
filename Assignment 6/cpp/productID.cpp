#include "productID.h"

productID::productID(std::shared_ptr<std::string>& in, const std::string& ss)  //constructor
{
	confirmStatement = in;   //save confirmation statement
	standardSerial = ss;     //save serial number
}

void productID::printStatement(void) const     //print confirmation
{
	std::cout << "Legal Confirmation Statement: [" << *confirmStatement << "] , producer country: " << countryName << std::endl;
}

std::ostream& operator<<(std::ostream& os, const productID& in)   //operator <<
{
	os << "Legal Confirmation Statement: [" << *(in.confirmStatement) << "]\nproducer country: " << in.countryName << " , serial number: " << in.standardSerial << std::endl;
	return os;
}