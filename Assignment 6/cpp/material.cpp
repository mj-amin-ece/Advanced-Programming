#include "material.h"

Material::Material(const std::string& name, double price, double weight, MAT_TYPE mt) : BasicGoods{name,GOODS_TYPE::CONSUMABLE,price }  //constructor
{
	this->weigth = weight;   //save weight material
	matType = mt;            //save material energy
}

double Material::getWeight(void) const  //get total weight
{
	return weigth + BasicGoods::weight;
}

double Material::getTaxPrice(void) const   //get tax price
{
	return basePrice * ((taxRate + MATERIAL_TAX) / 100);
}

double Material::getEndPrice(void) const   //get end price
{
	return basePrice * (1 + (taxRate + MATERIAL_TAX) / 100);
}

bool Material::operator==(const Material& in) const  //operator ==
{
	if (getBrandName() == in.getBrandName() && getGoodsType() == in.getGoodsType() && basePrice == in.basePrice && weigth==in.weigth)
		return true;
	return false;
}

bool Material::operator==(const BasicGoods& in) const
{
	if (typeid(in) != typeid(Material))
		return false;
	else
	{
		BasicGoods* temp{ const_cast<BasicGoods*>(&in) };
		Material* temp_2{ dynamic_cast<Material*>(temp) };
		return Material::operator==(*temp_2);
	}
}

