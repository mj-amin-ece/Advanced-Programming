#include "product.h"

Product::Product(const std::string& brandName, double price, double matWei, shared_str confirmation) : BasicGoods{ brandName,GOODS_TYPE::OBJECT,price }
	 ,Appliance{brandName,price,0.3} ,Material{brandName,price,matWei},productID{confirmation}
{   //constructor
	taxRate = TYPICAL_TAX_RATE;

	//set member variables
	BasicGoods::approxDim = std::make_shared < std::array<double, 3>>(std::array<double, 3>{0.3, 0.4, 1.2 * (1 + matWei)});
	BasicGoods::packing = PACK_TYPE::CARTON;
	Appliance::energyGrade = ENERGY_COST::LOW;
}

double Product::getTaxPrice(void) const  //get tax price
{
	if (energyGrade == ENERGY_COST::HIGH)
		return BasicGoods::basePrice * ((taxRate + APPLIANCE_EXTRA_TAX_HIGH) / 100);
	else
		return BasicGoods::basePrice * ((taxRate + APPLIANCE_EXTRA_TAX_MEDIUM) / 100);
}

double Product::getEndPrice() const   //get end price
{
	if (energyGrade == ENERGY_COST::HIGH)
		return BasicGoods::basePrice * (1 + (taxRate + APPLIANCE_EXTRA_TAX_HIGH) / 100);   //for hight energy
	else
		return BasicGoods::basePrice * (1 + (taxRate + APPLIANCE_EXTRA_TAX_MEDIUM) / 100);  //other wise
}

double Product::getWeight(void) const  //get total weight 
{
	return BasicGoods::weight + Material::weigth + Appliance::weight;
}

void Product::setTaxRate(double newTax)  //set tax rate
{
	taxRate = newTax;
}

void Product::setOriginCountry(const std::string& cnt)  //set origin country
{
	BasicGoods::setOriginCountry(cnt);
	countryName = cnt;
}

bool Product::operator==(const BasicGoods& in) const    //operator ==
{
	if (typeid(in) != typeid(Product))
		return false;
	else
		return Product::operator==(in);
}

bool Product::operator==(const Product& in) const
{
	if (getBrandName() == in.getBrandName() && getGoodsType() == in.getGoodsType() && getBaseprice() == in.getBaseprice())
		return true;
	return false;
}
