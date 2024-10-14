#ifndef __BASIC_GOODS_HEADER__
#define __BASIC_GOODS_HEADER__

#include<iostream>
#include<string>
#include<memory>
#include<array>

enum class PACK_TYPE
{
	UNKNOWN,
	RAW,
	CAN,
	NYLON,
	CARTON,
	BARREL
};

enum class GOODS_TYPE
{
	CONSUMABLE,
	DISPOSABLE,
	OBJECT
};

class BasicGoods
{
protected:
	PACK_TYPE packing;
	double weight;                      //approx weight of packing! not the commodity
	std::shared_ptr< std::array<double, 3> > approxDim;  //dimentions
	double basePrice;                    // value in euro or dollar 
	double taxRate;                      // in percent

	void setNewPrice(double price);      //set new base price

private:
	char* brandName;                     //brand name
	GOODS_TYPE goodsType;
	char* originCountry;

public:
	BasicGoods(const std::string& bName, GOODS_TYPE gTyp, double price);  //constructor
	virtual ~BasicGoods();                                        //destructor

	constexpr static double INITIAL_TAX_RATE = 5;

	// getters
	std::string getBrandName(void) const;
	double getBaseprice(void) const;
	GOODS_TYPE getGoodsType(void) const;
	virtual double getWeight(void) const;
	virtual double getVolume(void) const;
	virtual double getEndPrice(void) const;
	virtual double getTaxPrice(void) const;

	// setters
	virtual void setOriginCountry(const std::string& cnt);
	void setAppearance(PACK_TYPE pck, std::shared_ptr< std::array<double, 3> > dimen);

	// operators
	virtual bool operator== (const BasicGoods& in) const ;
	virtual bool operator< (const BasicGoods& in) const;
};


#endif // __GOODS_HEADER__


