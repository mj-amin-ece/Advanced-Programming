#ifndef __PRODUCT_HEADER__
#define __PRODUCT_HEADER__

#include "material.h"
#include "appliance.h"
#include "productID.h"
#include <string>


using shared_str = std::shared_ptr<std::string>;


class Product : public Appliance, public Material, public productID
{
private:
	double taxRate;   //tax rate product
public:
	Product(const std::string& brandName, double price, double matWei, shared_str confirmation);   //constructor
	~Product() = default;  //destructor

	constexpr static double TYPICAL_TAX_RATE = 23;

	//getter
	double getTaxPrice(void) const;   //get tax price
	double getEndPrice() const;   //get end price
	double getWeight(void) const;  //get totol weight

	//setter
	void setTaxRate(double newTax);   //set new tax rate oroduct
	void setOriginCountry(const std::string& cnt);  //set origin country 

	//opertator
	bool operator== (const BasicGoods& in) const;   
	bool operator== (const Product& in) const;
};

#endif // __PRODUCT_HEADER__
