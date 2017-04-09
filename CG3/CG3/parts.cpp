#include "parts.h"

double fpart(double x)
{
    double intpart = 0;
    double fp =  modf(x, &intpart);
    if (fp < 0) {
        fp += 1;
    }
    return fp;
}

int ipart(double x)
{
    double intpart = 0;
    modf(x, &intpart);
    return (int) intpart;
}
