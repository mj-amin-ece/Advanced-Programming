
#ifndef __FOOD_COMMODITY_HEADER__
#define __FOOD_COMMODITY_HEADER__
#include<ctime>
#include "basicGoods.h"


enum class FOOD_MODE   //to classifiy food
{
	LIQUID,
	CREAM,
	SOLID
};

class Food : public BasicGoods
{
private:
	FOOD_MODE mode;
	double netWeight;          //weight of food
	std::time_t expirationTime;

public:

	Food(const std::string& name, double price, double Wei, FOOD_MODE md=FOOD_MODE::SOLID);  //constructor
	~Food()=default;  //destructor

	constexpr static double FOOD_TAX_SUBSIDE = 3; // subtract this!

	// getters
	double getEndPrice(void) const;           //get end price 
	double getTaxPrice(void) const override;  //get tax price
	double getWeight(void) const;             //get total weight
	std::time_t getRemainingExp(void) const;  //get remain expiration time

	// setters
	void setExpiration(std::time_t t);  //set exp
	void setFoodMode(FOOD_MODE md);     //set mode food

	//operator
	bool operator== (const BasicGoods& in) const;  
	bool operator< (const BasicGoods& in) const;
	bool operator== (const Food& in) const ;
	bool operator< (const Food& in) const ;

};

#endif // __FOOD_COMMODITY_HEADER__


