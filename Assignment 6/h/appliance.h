#ifndef __APPLIANCE_COMMODITY_HEADER__
#define __APPLIANCE_COMMODITY_HEADER__
#include "basicGoods.h"

enum class ENERGY_COST
{
	IRRELEVANT,
	LOW,
	MEDIUM,
	HIGH
};

class Appliance : virtual public BasicGoods
{
protected:
	double weight;                            // which is netWeight
	ENERGY_COST energyGrade;                  //energy grade

	double getEndPrice(void) const override;  //get end price

public:

	Appliance(const std::string& name, double price, double Wei); //constructor
	~Appliance() = default;   //destructor


	constexpr static double APPLIANCE_EXTRA_TAX_HIGH = 17;
	constexpr static double APPLIANCE_EXTRA_TAX_MEDIUM = 7;

	using BasicGoods::setNewPrice;   //use setnewPrice for appliance as public
	using BasicGoods::approxDim;     //use approxDim for appliace as public

	//getter 
	double getWeight(void) const ;     //get total weight
	double getTaxPrice(void) const;    //get end price

	//setters
	void setWeight(double w);          //set  weight appliance
	void setEnergyGrade(ENERGY_COST ec); //set energy Grade

	//oprator
	bool operator== (const BasicGoods& in) const; 
	bool operator==(const Appliance& in);

};


#endif // __APPLIANCE_COMMODITY_HEADER__
