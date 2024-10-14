#include "basicGoods.h"
#include<string.h>

BasicGoods::BasicGoods(const std::string& bName, GOODS_TYPE gTyp, double price) //constructor
{
	brandName = strdup(bName.c_str());    //convert string to char*
	
	goodsType = gTyp;                   //save goodsType
	basePrice = price;                 //save base price

	originCountry = nullptr;           //initialize country
	taxRate = INITIAL_TAX_RATE;        //initialize tax rate
	packing = PACK_TYPE::UNKNOWN;      //initialize packing
	weight = 0.1;                      //initialize weight
}

BasicGoods::~BasicGoods()        //destructor
{
	free(brandName);
	free(originCountry);
}

double BasicGoods::getEndPrice(void) const   //get end price
{
	return basePrice * (1 + taxRate / 100);
}

double BasicGoods::getTaxPrice(void) const   //get tax price
{
	return basePrice * (taxRate / 100);
}

std::string BasicGoods::getBrandName(void) const  //get brand name
{
	return brandName;
}

double BasicGoods::getBaseprice(void) const   //get base price
{
	return basePrice;
}

GOODS_TYPE BasicGoods::getGoodsType(void) const  //get goods type
{
	return goodsType;
}

double BasicGoods::getWeight(void) const  //get weight
{
	return weight;
}

double BasicGoods::getVolume(void) const   //get volume
{
	return (*(approxDim.get()->begin())) * (*(approxDim.get()->begin() + 1)) * (*(approxDim.get()->begin() + 2));
}

void BasicGoods::setOriginCountry(const std::string& cnt)  //set country
{
	originCountry = strdup(cnt.c_str());           //convert string to char*
}

void BasicGoods::setNewPrice(double price)    //set new base price
{
	basePrice = price;
}

void BasicGoods::setAppearance(PACK_TYPE pck, std::shared_ptr<std::array<double, 3>> dimen)  //set new approxdim and packing
{
	packing = pck;
	approxDim = dimen;
}

bool BasicGoods::operator==(const BasicGoods& in) const   //operator ==
{
	if (typeid(in) == typeid(BasicGoods) && goodsType == in.goodsType && *brandName == *in.brandName && basePrice == in.basePrice)
		return true;
	return false;
}

bool BasicGoods::operator<(const BasicGoods& in) const  //operator <
{
	if (getEndPrice() < in.getEndPrice())
		return true;
	return false;
}


