#include "truncate.h"

#include <cassert>
#include <cmath>

/**
 * @brief integrale part of a float (floor)
 *
 * @param x
 * @return double
 */
double ipart(double x)
{
    return std::floor(x);
}

/**
 * @brief Decimal part of a float
 *
 * @param x
 * @return double
 */
double dpart(double x)
{
    return x - ipart(x);
}

// tronc un nombre après le bit 2^l

/**
 * @brief truncate bits after bit 2^l
 *
 * @param x number to truncate
 * @param l power of lsb to keep
 * @return truncated number
 */
double truncinf(double x, int l)
{
    double p = pow(2, l);
    double y = floor(x / p) * p;
    assert(y <= x);
    return y;
}

/**
 * @brief truncate bits after bit 2^l and add 2^l
 *
 * @param x number to truncate
 * @param l power of lsb to keep
 * @return truncated number
 */
double truncsupxxx(double x, int l)
{
    double p = pow(2, l);
    double y = floor(x / p + 1) * p;
    assert(x <= y);
    return y;
}
double truncsup(double x, int l)
{
    return truncinf(x, l) + pow(2, l);
}

I truncInterval(I i, int l)
{
    return I(truncinf(i.lower(), l), truncsup(i.upper(), l));
}

/**
 * @brief Least Common Bit between x and y
 *
 * @param x
 * @param y
 * @return int
 */
int lcb(double x, double y)
{
    int dn = 0;
    while ((ipart(x) == ipart(y)) && (dn > -53)) {
        x = dpart(x) * 2;
        y = dpart(y) * 2;
        dn--;
    }
    return dn;
}

/**
 * @brief Least Common Bit betwwen the boundaries of i
 *
 * @param i interval
 * @return int
 */
int lcb(I i)
{
    return lcb(i.lower(), i.upper());
}

/**
 * @brief Most Significant Bit of abs(x)
 *
 * @param x
 * @return int
 */
int msb(double x)
{
    return int(log2(fabs(x))) + 1;
}

/**
 * @brief Most Significant Bit
 *
 * @param i interval
 * @return int
 */
int msb(I i)
{
    return std::max(msb(i.lower()), msb(i.upper()));
}