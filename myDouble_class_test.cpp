#include "myDouble.h"
#include <iostream>
int main(void)
{
    myDouble num1(5);
    myDouble num2(3);

    std::cout<<(num1^num2)<<std::endl;
    std::cout<<(num1^2)<<std::endl;
}