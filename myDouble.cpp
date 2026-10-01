#include "myDouble.h"


myDouble::myDouble(double value)
{
    this->value = value;
}

double myDouble::operator^(const myDouble& n)
{
    return pow(value,n.value);
}

double myDouble::operator^(double n)
{
    return pow(value,n);
}

double myDouble::operator+(const myDouble& n)
{
    return value + n.value;
}

double myDouble::operator-(const myDouble& n)
{
    return value - n.value;
}

double myDouble::operator*(const myDouble& n)
{
    return value * n.value;
}

double myDouble::operator/(const myDouble& n)
{
    return value / n.value;
}