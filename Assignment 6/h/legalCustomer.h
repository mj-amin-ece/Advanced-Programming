#ifndef __LEGAL_CUSTOMER_HEADER__
#define __LEGAL_CUSTOMER_HEADER__
#include "customer.h"

class LegalCustomer : public Customer
{
private:
	std::string companyName;   //company name

public:
	LegalCustomer(const std::string& corrName, const std::string& compName);  //constructor
	~LegalCustomer() = default;      //destructor

	//opeartor
	virtual bool operator==(const Customer& in) const override;
	virtual bool operator<(const Customer& in) const override;
	bool operator==(const LegalCustomer& in) const;
	bool operator<(const LegalCustomer& in) const;
};

#endif //

