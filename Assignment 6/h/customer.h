#ifndef __CUSTOMER_HEADER__
#define __CUSTOMER_HEADER__
#include <string>
#include <vector>
#include <memory>
#include<sstream>
#include "basicGoods.h"
#include  <queue>
#include "SharedComps.hpp"
#include <algorithm>

class Customer
{
protected:
    std::string name;      //customer name
    double totalChargedTax;  //total tax price
    std::deque< std::shared_ptr<BasicGoods> > assets;   //all goods
    double assetValue;   //total end price

public:
    explicit Customer(const std::string& name);  //constructor
    virtual ~Customer() = default;               //destructor


    // simple functions 
    using sharedBG = std::shared_ptr<BasicGoods>; 
    std::string printBasicInfo(void) const;    //print info

    // getter
    double getTotalAsset(void) const;       //get asset value
    double getTotalChargedTax(void) const;  //ger total charged tax
    std::string getName(void) const;        //get name
    std::deque< std::shared_ptr<BasicGoods> > getassets(void);  //all goods

    // importers
    virtual void importNewGoods(std::shared_ptr<BasicGoods>);   //add new good

    template<class Iter>
    void importNewGoods(Iter start, Iter end);  //add new goods

    template <class T>
    void findGoods( std::deque< sharedBG >& list, T comp);  //find specific goods


    template <typename T>       
    bool queueGoods(std::priority_queue< sharedBG, std::deque<sharedBG>, Shared_less<BasicGoods> >& Q);  //find same kind goods

    // operators
    virtual bool operator==(const Customer& in) const = 0;   
    virtual bool operator<(const Customer& in) const = 0;
};

template<class Iter>
void Customer::importNewGoods(Iter start, Iter end)   //add new goods
{
     if (start == end)
        assets.push_back(*start);
    for (auto it{ start }; it != end; it++)
        importNewGoods(*it);
}

template<class T>
void Customer::findGoods(std::deque<sharedBG>& list, T comp)  //find specific goods
{
    auto it = std::copy_if(assets.begin(), assets.end(), list.begin(), comp);
    list.resize(std::distance(list.begin(), it));    //resize out put
}

template<typename T>
bool Customer::queueGoods(std::priority_queue<sharedBG, std::deque<sharedBG>, Shared_less<BasicGoods>>& Q)  //find same kind goods
{   
    for (size_t i{}; i < assets.size(); i++)
        if (typeid(T) == typeid(*assets[i].get()))
            Q.push(assets[i]);
    
    if (Q.empty())
       return false;
    return true;
}
#endif // __CUSTOMER_HEADER__

