#ifndef __PRODUCTID_HEADER__
#define __PRODUCTID_HEADER__
#include<iostream>
#include <string>
#include <memory>

class productID
{
protected:
	std::string standardSerial;   //serail number
	std::shared_ptr< std::string > confirmStatement; //confirmation satatment 
	std::string countryName;   //country name


public:
	productID(std::shared_ptr< std::string >& in, const std::string& ss = {});  //constructor

	void printStatement(void) const;   //print confirmation
	friend std::ostream& operator<<(std::ostream& os, const productID& in); //operator <<
};

#endif // __PRODUCTID_HEADER__
