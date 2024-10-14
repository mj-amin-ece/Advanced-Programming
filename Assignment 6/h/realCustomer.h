#ifndef __REAL_CUSTOMER_HEADER__
#define __REAL_CUSTOMER_HEADER__
#include "customer.h"
#include <string>

class RealCustomer : public Customer
{
private:
	long int nationalID;   //national ID

public:

	RealCustomer(const std::string& name, long int nid=0);   //constructor
	~RealCustomer() = default;        //destructor

	long int getNationalID(void);    //get national ID

	//operators
	virtual bool operator==(const Customer& in) const override;
	virtual bool operator<(const Customer& in) const override;
	bool operator==(const RealCustomer& in) const;
	bool operator<(const RealCustomer& in) const;
};

#endif // __REAL_CUSTOMER_HEADER__
