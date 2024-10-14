#include "customer.h"

Customer::Customer(const std::string& name)  //constructor
{
	this->name = name;     //save name
	assetValue = 0;        //initialize asswetValue
	totalChargedTax = 0;   //initialize total charged tax
}

std::string Customer::printBasicInfo(void) const    //print info
{
	std::ostringstream print_InFo{};
	print_InFo << name << " >> No of assets: " << assets.size() << ", Total Assest: " << assetValue << ", Charged Tax: " << totalChargedTax;
	return print_InFo.str();
}

double Customer::getTotalAsset(void) const   //get total asset
{
	return assetValue;
}

double Customer::getTotalChargedTax(void) const  //get total charged tax
{
	return totalChargedTax;
}

std::string Customer::getName(void) const   //get name
{
	return name;
}

std::deque<std::shared_ptr<BasicGoods>> Customer::getassets(void)  //get assets (goods)
{
	return assets;
}

void Customer::importNewGoods(std::shared_ptr<BasicGoods> in)    //add new good
{ 
	assets.push_back(in);                  //add new good
	totalChargedTax += in->getTaxPrice();  //update total charged tax
	assetValue += in->getEndPrice();       //update asset value
}



