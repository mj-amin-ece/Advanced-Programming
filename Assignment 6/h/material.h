#ifndef __MATERIAL_HEADER__
#define __MATERIAL_HEADER__

#include "basicGoods.h"

enum class MAT_TYPE   //to classifiy material
{
	NORMAL,
	FLAMABLE,
	HAZARDOUS
};


class Material : virtual public BasicGoods
{
protected:
	double weigth;   //weight material
	MAT_TYPE matType;//material type

public:
	Material(const std::string& name, double price , double weight, MAT_TYPE mt=MAT_TYPE::NORMAL);   //constructor
	~Material() = default;   //destructor

	constexpr static double MATERIAL_TAX = 1.5;


	// getters
	double getWeight(void) const;   //get total weight
	double getTaxPrice(void) const;  //get tax pice
	double getEndPrice(void) const;  //get end price

	//operator
	bool operator==(const Material& in) const;
	bool operator== (const BasicGoods& in) const;
};

#endif // __MATERIAL_HEADER__

