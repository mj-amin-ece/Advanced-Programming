#include <iostream>
#include "gtest/gtest.h"
#include"apmidterm.h"

int main(int argc, char **argv)
{
    
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    std::cout << "Here!"<<std::endl;
    if (!ret)
        std::cout << "<<<SUCCESS>>>" << std::endl;
    else
        std::cout << "FAILED" << std::endl;
        
    return 0;
}
