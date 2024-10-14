#include <iostream>
#include "gtest/gtest.h"
#include "food.h"
#include "appliance.h"
#include "material.h"
#include "productID.h"
#include "product.h"
#include "realCustomer.h"
#include "legalCustomer.h"
#include "Storehouse.h"


template <class T>
bool eq( const T& a, const T& b)
{
	return std::abs(a-b) < 0.0001;
}


namespace
{
    TEST (ST_Begin, check)
	{
		double A{96.6};
		EXPECT_EQ(A , 96.6) << "Yout GTesting has some issues!";
	}
	
	TEST (ST_Goods, Basic)
	{
		BasicGoods bg1 {"Mug", GOODS_TYPE::OBJECT, 5};
		BasicGoods bg2 {"Mug", GOODS_TYPE::OBJECT, 5};
		BasicGoods bg3 {"Bag", GOODS_TYPE::DISPOSABLE, 1};

		EXPECT_EQ (bg1.getEndPrice() , 5.25) ;
		EXPECT_EQ (bg1.getTaxPrice() , 0.25) ;

		std::array<double,3> volume9 {2,1.5,3};
		auto V1 = std::make_shared< std::array<double,3> > (volume9);
		
		bg1.setAppearance(PACK_TYPE::CARTON, V1);

		EXPECT_EQ (bg1.getVolume() , 9);
		EXPECT_EQ (true, bg1 == bg2);
		EXPECT_EQ (false, bg1 == bg3);
		EXPECT_EQ (true, bg3 < bg1);
		
		EXPECT_EQ (std::string("Bag"), bg3.getBrandName());
	}
	
	TEST (ST_Goods, Food)
	{
		Food f1 {"Salad", 3.5, 0.5};
		Food f2 {"Cheese", 17, 1.5, FOOD_MODE::CREAM};

		std::time_t now = std::time(nullptr);
		now += 4*24*3600;
		f1.setExpiration(now);
		
		EXPECT_EQ (f2.getEndPrice(), 17.34);
		EXPECT_EQ (eq(f2.getVolume(), 0.054) , true);
		EXPECT_EQ (true, f1 < f2);
	}
	
	TEST (ST_Goods, Appliance)
	{
		Appliance ag1 {"TV", 300, 5};
		ag1.setEnergyGrade(ENERGY_COST::HIGH);
		Appliance ag2 {"TV", 300, 5};

		EXPECT_EQ (true, ag2 < ag1);
		
		EXPECT_EQ (false, ag1 == ag2) << "!";
		ag2.setEnergyGrade(ENERGY_COST::HIGH);
		EXPECT_EQ (true, ag1 == ag2) << "@";
		
		
		std::array<double,3> volume3( {0.5,2,3} );
		ag2.approxDim = std::make_shared<std::array<double,3>>(volume3);

		BasicGoods& bgp = ag2;
		EXPECT_EQ (eq(bgp.getVolume(),3.0) , true);
		EXPECT_EQ (false , ag2<bgp);
	}
	
	TEST (ST_Goods, Material)
	{
		Material mg1 {"Paper", 40, 65, MAT_TYPE::FLAMABLE};
		Material mg2 {"Cement", 100, 250};
		Material mg3 {"Cement", 100, 100};
		
		EXPECT_EQ (eq(mg1.getEndPrice(), 42.6), true);
		EXPECT_EQ (mg2.getWeight(), 250.1);
		EXPECT_EQ (false, mg2 == mg3);

		BasicGoods bg1 {"Cement", GOODS_TYPE::CONSUMABLE, 100};
		EXPECT_EQ (false , mg2 == mg3);
		EXPECT_EQ (false , bg1 == mg3);
	}
	
	TEST (ST_Goods, Product)
	{
		auto Arsh_LIC = std::make_shared<std::string> ("Arsh is a Registered Co.");
		
		Product pg1 {"Refrigerator", 1500, 5, Arsh_LIC};
		Product pg2 {"Refrigerator", 1700, 5, Arsh_LIC};
		Product pg3 {"S400", 2000, 20, Arsh_LIC};

		BasicGoods bg1 {"S400" , GOODS_TYPE::OBJECT, 2500};
		BasicGoods bg2 {"S500" , GOODS_TYPE::OBJECT, 1000};
		
		EXPECT_EQ ( true, pg1 < pg2);
		EXPECT_EQ ( false, bg1 == pg3);
		EXPECT_EQ ( true, pg3 < bg1);
		EXPECT_EQ ( false, bg1 < pg3);
		EXPECT_EQ ( true, bg2 < pg3);

		pg3.setNewPrice(500);
		pg3.setOriginCountry("China");
		
		std::ostringstream buf{};
		buf << pg3;

		EXPECT_EQ ( buf.str() ,
	    "Legal Confirmation Statement: [Arsh is a Registered Co.]\nproducer country: China , serial number: \n");
		
	}
	
	TEST (ST_Customer, Reals)
	{
		RealCustomer Neda {"NedaSoltani", 778};

		Neda.importNewGoods(std::make_shared<Material> ("H2O2", 50, 15));
		Neda.importNewGoods(std::make_shared<Food> ("Corn", 4, 1.5));
		Neda.importNewGoods(std::make_shared<Food> ("Corn", 4, 2.2));

		EXPECT_EQ ( eq(Neda.getTotalAsset(), 61.41) , true);
		EXPECT_EQ ( eq(Neda.getTotalChargedTax(), 3.41) , true);
		EXPECT_EQ (true, Neda==Neda);
	}
	TEST (ST_Customer, Legals)
	{
		LegalCustomer Beta{"Pajan","Beta Co"};

		Beta.importNewGoods( std::make_shared<BasicGoods>("Saw", GOODS_TYPE::OBJECT, 3) );
		Beta.importNewGoods( std::make_shared<Appliance> ("flash", 45, 0.2));

		EXPECT_EQ ( eq(Beta.getTotalAsset(), 53.55) , true);
	}
	TEST (ST_Customer, CUSTOMER)
	{
		RealCustomer Kv  {"Keyvan", 445};
		RealCustomer Kv2 {"Keyvan", 445};
		RealCustomer Ma  {"Marjan", 312};
		LegalCustomer HP {"David Packard","HP"};

		std::vector<Customer::sharedBG> goods{};

		goods.push_back( std::make_shared<Appliance>  ("Crusher", 100, 3.4) );
		goods.push_back( std::make_shared<Appliance>  ("Juicer", 56, 2.5) );
		goods.push_back( std::make_shared<Material>   ("Dye-Red", 12, 10) );
		goods.push_back( std::make_shared<Material>   ("Gass", 50, 100) );
		goods.push_back( std::make_shared<Food>       ("Jelly", 35, 15) );
		goods.push_back( std::make_shared<Food>       ("Carrot", 10, 50) );
		goods.push_back( std::make_shared<BasicGoods> ("N95", GOODS_TYPE::DISPOSABLE, 1) );
		goods.push_back( std::make_shared<Material>   ("Alchol", 20, 1.5, MAT_TYPE::FLAMABLE) );
		
		Kv.importNewGoods(goods.begin(), goods.begin()+5);
		Kv2.importNewGoods(goods.begin()+2, goods.begin()+4);
		Ma.importNewGoods(std::make_shared<Food> ("Cheese", 50, 50) );
		Ma.importNewGoods(std::make_shared<Food> ("Cream", 30, 12, FOOD_MODE::CREAM) );
		Ma.importNewGoods(goods.begin(),goods.end());
		HP.importNewGoods(goods.begin()+3, goods.end());

		EXPECT_EQ (true, Kv==Kv2);
		EXPECT_EQ (false, Kv==HP);
		EXPECT_EQ (true, Kv<HP);
		EXPECT_EQ (false, Kv<Kv2);

		// create an empty queue to fill with Foods
		using shBG = std::shared_ptr<BasicGoods>;
		std::priority_queue< shBG, std::deque<shBG> , Shared_less<BasicGoods> > mQ;

		// fill it 
		Ma.queueGoods<Food>(mQ);

		// find whats in it
		std::ostringstream buf;
		while (!mQ.empty())
		{
			auto item = mQ.top();
			buf << item->getBrandName() << " > " << item->getEndPrice() << ",";
			mQ.pop();
		}
		EXPECT_EQ ( std::string("Cheese > 51,Jelly > 35.7,Cream > 30.6,Carrot > 10.2,") , buf.str());
	}
	
	TEST (ST_Stoorehouse, Store)
	{
		Storehouse BAport {"BandarAbbas National Port"};

		auto ParsianLIC = std::make_shared<std::string> ("Parsian is Highly proficient Group!");

		auto Sadeghi = std::make_shared<RealCustomer> ("Sadeghi Hariry" , 9180);
		std::shared_ptr<Customer> pC = Sadeghi;

		pC->importNewGoods( std::make_shared<Product>   ("MotorDriver", 5000, 0, ParsianLIC) );
		pC->importNewGoods( std::make_shared<Product>   ("PowerSupply", 300, 10, ParsianLIC) );
		pC->importNewGoods( std::make_shared<Product>   ("MainBoard", 2000, 0, ParsianLIC)   );
		pC->importNewGoods( std::make_shared<Appliance> ("AMD Ryzen", 750, 0.6) );

		
		auto Ehsan = std::make_shared<RealCustomer> ("Sadeghi Hariry" , 9180);
		pC = Ehsan;

		pC->importNewGoods( std::make_shared<Appliance> ("Dishwasher", 1200, 12.7));
		pC->importNewGoods( std::make_shared<Appliance> ("Moblie", 320, 0.4));


		auto MCI = std::make_shared<LegalCustomer> ("MehdiAkhavan","MCI");
		pC = MCI;

		pC->importNewGoods( std::make_shared<Appliance> ("GSM repeater", 500, 1.1) );
		pC->importNewGoods( std::make_shared<Appliance> ("Antenna", 100, 0.5) );


		BAport.newCustomer(Sadeghi);
		BAport.newCustomer(Ehsan);
		BAport.newCustomer(MCI);

		std::ostringstream buf{};
		buf << BAport.printCustomers();
        
        // THIS IS TRUE IF YOU DONT WRITE THE BONUS PART OF STOREHPUSE
        // (that is: when you are NOT COPYING the duplicate customer to the present customer in the SET)
		std::string w = "Legal: MehdiAkhavan >> No of assets: 2, Total Asset: 672, Charged Tax: 72\nReal: Sadeghi Hariry >> No of assets: 4, Total Asset: 9819, Charged Tax: 2280\n";
		//EXPECT_EQ (buf.str() , w);

	}
}

