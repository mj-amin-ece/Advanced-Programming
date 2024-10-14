#include <limits.h>
#include "aphw1.h"
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
namespace
{
TEST(APHW1Test, getDataFunctionTest)
{
    std::vector<std::vector<double>> data{getData("AP-Data.csv")};
    std::cout << "getData Test here!" << std::endl;
    EXPECT_EQ(1, data[0][0]);
    EXPECT_EQ(14.23, data[0][7]);
}
TEST(APHW1Test, gradeFunctionTest)
{
    std::vector<double> student{1, 2, 3, 4, 5, 6, 7};
    std::vector<double> w (7, 1);
    std::cout << "grade Test here!" << std::endl;
    EXPECT_EQ(28, grade(w, student));
}
TEST(APHW1Test, costFunctionTest)
{
    std::vector<std::vector<double>> data{getData("AP-Data.csv")};
    std::vector<double> w (7, 1);
    std::cout << "CostFunction Test here!" << std::endl;
    EXPECT_TRUE((45 < J(w, data)) && (52 > J(w, data)));
}
TEST(APHW1Test, trainFunctionTest)
{
    std::vector<std::vector<double>> data{getData("AP-Data.csv")};
    std::vector<double> w (7, 0);
    w = train(data, w, 0.01, 500, 0.01, false);
    std::cout<<"Weights...\n";
    for(size_t i{}; i<w.size(); std::cout << w[i++] << " ,");
    std::cout<<"\n";
    EXPECT_TRUE((w[0]>5) && (w[0]<6) && (w[6] > 2) && (w[6] < 3));
}
} 
