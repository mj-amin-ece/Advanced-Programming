#include <limits.h>
#include "aphw2.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "gtest/gtest.h"
namespace
{
TEST(APHW2Test, AddressingTest1)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 4});
    data.push_back(std::vector<double>{6, 7});
    Matrix a(data);
    EXPECT_EQ(2, a[0][0]);
}
TEST(APHW2Test, SumTest)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 4});
    data.push_back(std::vector<double>{6, 7});
    Matrix a(data);
    Matrix b(data);
    Matrix c = a + b;
    EXPECT_EQ(12, c[1][0]);
}
TEST(APHW2Test, MultiplicationTest)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 4});
    Matrix a(data);
    data.push_back(std::vector<double>{6, 7});
    Matrix b(data);
    Matrix c = a * b;
    EXPECT_EQ(28, c[0][0]);
}
TEST(APHW2Test, TransposeTest)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 4});
    Matrix a(data);
    Matrix b{a.T()};
    EXPECT_EQ(4, b[1][0]);
}
TEST(APHW2Test, InversionTest)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 8});
    data.push_back(std::vector<double>{0, 1});
    Matrix a(data);
    Matrix ainv{a.inv()};
    EXPECT_EQ(0.5, ainv[0][0]);
}
TEST(APHW2Test, DeterminantTest)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 8});
    data.push_back(std::vector<double>{0, 1});
    Matrix a(data);
    double det{a.det()};
    EXPECT_EQ(2, det);
}
TEST(APHW2Test, MultiplicationTest2)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double>{2, 4});
    data.push_back(std::vector<double>{6, 7});
    data.push_back(std::vector<double>{2, 5});
    Matrix a(data);
    Matrix b{a * a.T()};
    EXPECT_EQ(20, b[0][0]);
}
TEST(APHW2Test, getDataTest)
{
    std::vector<std::vector<double>> data{getData("AP-Data.csv")};
    EXPECT_EQ(1, data[0][0]);
}
TEST(APHW2Test, estimationTest)
{
    std::vector<std::vector<double>> my_data{getData("AP-Data.csv")};
    Matrix X{my_data};
    Matrix y{X.col(7)};
    X.delCol(7);
    Matrix c{(X.T()*X).inv()};
    Matrix d{X.T()};
    Matrix w{c * d *y};
    EXPECT_TRUE((w[1][0] > 8) && (w[1][0] < 9));
    EXPECT_TRUE((w[2][0] > 4.5) && (w[2][0] < 5.5));
}
} 
