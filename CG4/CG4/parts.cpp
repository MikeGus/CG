#include "parts.h"

double fpart(double x)
{
    double intpart = 0;
    return modf(x, &intpart);
}

int ipart(double x)
{
    double intpart = 0;
    modf(x, &intpart);
    return (int) intpart;
}
