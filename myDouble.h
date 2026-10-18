#ifndef MY_DOUBLE_CLASS
#define MY_DOUBLE_CLASS

#include <cmath>

class myDouble{
    private:
        double value;
    public:
        myDouble(double value);
    
        double operator^(const myDouble& n);
        
        double operator^(double n);
    
        double operator+(const myDouble& n);
        
        double operator-(const myDouble& n);
    
        double operator*(const myDouble& n);
    
        double operator/(const myDouble& n);
};
#endif