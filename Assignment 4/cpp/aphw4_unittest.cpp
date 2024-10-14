#include <limits.h>
#include "aphw4.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "gtest/gtest.h"
namespace
{
TEST(APHW4Test, StudentTest)
{
    Student a{9423013, 80, 95, 90};
    Student b{9423091, 100, 100, 100, 100};
    a.show();
    EXPECT_TRUE(a.value()>-39 && a.value()<-38);
}
TEST(APHW4Test, APDSTest)
{
    Student a{9423013, 80, 95, 90};
    Student b{9423091, 100, 100, 100, 100};
    APDS apds;
    apds.push(a);
    apds.push(b);
    EXPECT_EQ(2, apds.getSize());
    EXPECT_EQ(3, apds.getCapacity());
}
TEST(APHW4Test, dataTest)
{
    std::vector<Student> apstudents{getData("APHW4Data.csv")};
    APDS apds{apstudents, 10};
    EXPECT_EQ(10, apds.getSize());
    Student* head{apds.getHeadStudent()};
    EXPECT_TRUE((head->value() > 57) && (head->value() < 58) );
}
} 
