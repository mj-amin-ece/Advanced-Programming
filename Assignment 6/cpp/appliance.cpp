#include "appliance.h"

double Appliance::getEndPrice(void) const    //get end price
{
	if (energyGrade == ENERGY_COST::HIGH)   //high
		return basePrice * (1 + (taxRate + APPLIANCE_EXTRA_TAX_HIGH) / 100);
	return basePrice * (1 + (taxRate + APPLIANCE_EXTRA_TAX_MEDIUM) / 100);  //otherwise
}

Appliance::Appliance(const std::string& name, double price, double Wei) : BasicGoods{name,GOODS_TYPE::OBJECT,price}  //constructor
{
	weight = Wei;   //save weight appliance
	energyGrade = {};  //initialize energy garade
}

double Appliance::getWeight(void) const //get total weight
{
	return BasicGoods::weight + weight;
}

double Appliance::getTaxPrice(void) const    //get tax price
{
	if (energyGrade == ENERGY_COST::HIGH)  //energy high
		return basePrice * ((taxRate + APPLIANCE_EXTRA_TAX_HIGH) / 100);
	return basePrice * ((taxRate + APPLIANCE_EXTRA_TAX_MEDIUM) / 100);  //other wise
}

void Appliance::setWeight(double w)   //set weight appliance
{
	weight = w;
}

void Appliance::setEnergyGrade(ENERGY_COST ec)  //set energy grade
{
	energyGrade = ec;
}

bool Appliance::operator==(const BasicGoods& in) const  //operator ==
{
	if(typeid(in)!=typeid(Appliance))
		return false;
	else
	{
		BasicGoods* temp{ const_cast<BasicGoods*>(&in) };
		Appliance* temp_2{ dynamic_cast<Appliance*>(temp) };
		return Appliance::operator==(*temp_2);
	}
}

bool Appliance::operator==(const Appliance& in)  
{
	if (getBrandName() == in.getBrandName() && getGoodsType() == in.getGoodsType() && basePrice == in.basePrice 
			&& energyGrade == in.energyGrade && Appliance::weight==in.weight)
		return true;
	return false;
}