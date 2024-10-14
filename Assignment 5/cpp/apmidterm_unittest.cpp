#include <limits.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "gtest/gtest.h"
#include "exponentialstudent.h"
#include "normalstudent.h"
#include "apqueue.h"
#include "apmidterm.h"

namespace
{
TEST(APMidtermTest, NormalStudentTest)
{
    NormalStudent mha{"MHA", 18, 2};
    EXPECT_TRUE(mha(19)>.1759 && mha(19)<.1762)<<std::setw(100) <<" ********minus 5 points\n";
    EXPECT_TRUE(mha(15, 20)>0.77 && mha(15,20)<0.78)<<std::setw(100) <<" ********minus 5 points\n";
}

TEST(APMidtermTest, ExponentialStudentTest)
{
    ExponentialStudent vh("VH", 0.01);
    EXPECT_TRUE(vh(10)>0.0080 && vh(10)<0.010)<<std::setw(100) <<" ********minus 5 points\n";
    EXPECT_TRUE(vh(0, 10)>0.094 && vh(0, 10)<0.096)<<std::setw(100) <<" ********minus 5 points\n";
}

TEST(APMidtermTest, APQueueTest1)
{
    std::vector<int> vec{28, 13, 49};
    APQueue<int> apq{vec};
    apq.show();
    std::cout<<std::setw(100) <<" ********minus 5 points if not printed beautifully!\n";
} 

TEST(APMidtermTest, APQueueTest2)
{
    APQueue<int> apq{std::vector<int>{28, 13, 49}};
    EXPECT_EQ(13, apq[1])<<std::setw(100) <<" ********minus 5 points if not printed beautifully!\n";
} 


TEST(APMidtermTest, APQueueTest3)
{
    std::vector<int> vec{28, 13, 49};
    APQueue<int> apq{vec};
    apq.enqueue(12);
    EXPECT_EQ(12, apq[3])<<std::setw(100) <<" ********minus 5 points\n";
}

TEST(APMidtermTest, APQueueTest4)
{
    APQueue<int> apq{std::vector<int>{28, 13, 49}};
    apq.enqueue(12)->enqueue(14)->enqueue(20);
    EXPECT_EQ(20, apq[5])<<std::setw(100) <<" ********minus 7 points\n";
}

TEST(APMidtermTest, APQueueTest5)
{
    APQueue<int> apq{std::vector<int>{28, 13, 49}};
    EXPECT_EQ(28, apq.dequeue())<<std::setw(100) <<" ********minus 5 points\n";
}

TEST(APMidtermTest, APQueueTest6)
{
    APQueue<int> apq{std::vector<int>{28, 13, 49}};
    apq.dequeue();
    apq.dequeue();
    apq.dequeue();
    apq.show();
    std::cout<<std::setw(100) <<" ********minus 5 points if did not print empty queue!\n";
}

TEST(APMidtermTest, APQueueTest7)
{
    APQueue<int> apq{std::vector<int>{28, 13, 49}};
    apq.dequeue();
    apq.dequeue();
    apq.dequeue();
    apq.dequeue();
    apq.dequeue();
    apq.enqueue(5);
    apq.show();
    EXPECT_EQ(5, apq[0])<<std::setw(100) <<" ********minus 8 points\n";
}

TEST(APMidtermTest, getDataTest)
{
    std::vector<std::unique_ptr<Student>> vec{getData("midterm.csv")};
    EXPECT_EQ(8, vec.size())<<std::setw(100) <<" ********minus 10 points\n";
}

TEST(APMidtermTest, APQueueTest8)
{
    APQueue<std::unique_ptr<Student>> apqueue1{getData("midterm.csv")};
    apqueue1.show();
    std::cout<<std::setw(100) <<" ********minus 10 points if did not print properly!\n";
}

TEST(APMidtermTest, APQueueTest9)
{
    APQueue<std::unique_ptr<Student>> apqueue1{getData("midterm.csv")};
    apqueue1.show();
    std::cout<<std::setw(100) <<" ********minus 10 points if did not print properly with 8 students!\n";
}

TEST(APMidtermTest, StudentTest)
{
    Student* ps{};
    NormalStudent mha{"MHA", 18, 2};
    ps = &mha;
    EXPECT_TRUE(ps->pdf(19)>.1759 && ps->pdf(19)<.1762)<<std::setw(100) <<" ********minus 10 points\n";
    ExponentialStudent vh("VH", 0.01);
    ps = &vh;
    EXPECT_TRUE(ps->pdf(10)>0.0080 && ps->pdf(10)<0.010)<<std::setw(100) <<" ********minus 5 points\n";
    EXPECT_TRUE(ps->between(0, 10)>0.094 && ps->between(0, 10)<0.096)<<std::setw(100) <<" ********minus 5 points\n";
}

}
