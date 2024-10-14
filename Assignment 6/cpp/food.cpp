#include "food.h"

Food::Food(const std::string& name, double price, double netWei, FOOD_MODE md) : BasicGoods{name,GOODS_TYPE::CONSUMABLE ,price} //constructor
{
	//initialize exp
	std::time_t now = std::time(nullptr); 
	now += 14 * 24 * 3600;
	expirationTime = now;

	netWeight = netWei;  //initialize weight food

	mode = md;           //save food mode

	//set dimension food and packing
	if (md == FOOD_MODE::LIQUID)  //for liquid
	{
		packing = PACK_TYPE::CAN;
		approxDim = std::make_shared < std::array<double, 3>>(std::array<double, 3>{0.3, 0.4, 0.2 * netWei});
	}
	else if (md == FOOD_MODE::CREAM)  //for cream
	{
		packing = PACK_TYPE::BARREL;
		approxDim = std::make_shared < std::array<double, 3>>(std::array<double, 3>{0.3, 0.4, 0.3 * netWei});
	}
	else if (md == FOOD_MODE::SOLID)  //for solid
	{
		packing = PACK_TYPE::NYLON;
		approxDim = std::make_shared < std::array<double, 3>>(std::array<double, 3>{0.3, 0.4, 0.7 * netWei});
	}
}

double Food::getEndPrice(void) const  //get end price
{
	return basePrice * (1 + (taxRate - FOOD_TAX_SUBSIDE) / 100);
}

double Food::getTaxPrice(void) const   //get tax price
{
	return basePrice * ((taxRate - FOOD_TAX_SUBSIDE) / 100);
}
 
double Food::getWeight(void) const   //get total weight
{
	return weight + netWeight;
}

std::time_t Food::getRemainingExp(void) const   //get remain exp from now
{
	return expirationTime - std::time(nullptr);
}

void Food::setExpiration(std::time_t t)   //set exp
{
	if (t - std::time(nullptr) >= 0)
		expirationTime = t;
	else
		std::cout << "invalid Time" << std::endl;
}

void Food::setFoodMode(FOOD_MODE md)    //set food mode
{
	mode = md;
}

bool Food::operator==(const BasicGoods& in) const   //operator ==
{
	if (typeid(in) != typeid(Food))
		return false;
	else
	{ 
		BasicGoods* temp{ const_cast<BasicGoods*>(&in) };
		Food* temp_2{ static_cast<Food*>(temp) };
		return Food::operator==(*temp_2);
	}
}

bool Food::operator<(const BasicGoods& in) const   //operator <
{	
	if (typeid(in) != typeid(Food))
	{
		if (getEndPrice() < in.getEndPrice())
			return true;
		else
			return false;
	}
	else
	{
		BasicGoods* temp{ const_cast<BasicGoods*>(&in) };
		Food* temp_2{ static_cast<Food*>(temp) };
		return Food::operator<(*temp_2);
	}
}

bool Food::operator==(const Food& in) const   //operator ==
{
	if (getBrandName()==in.getBrandName() && getGoodsType()==in.getGoodsType() && basePrice==in.basePrice && mode==in.mode)
		return true;
	return false;
}

bool Food::operator<(const Food& in) const    //opertor <
{
	if (expirationTime<in.expirationTime)
		return true;
	return false;
}
