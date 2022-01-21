#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "analyze.h"
#include "truncate.h"

/**
 * @brief Compute the precision histogram
 *
 * @param fun unary interval function
 * @param i input interval
 * @param l LSB precision
 * @return std::map<int, int>
 */
std::map<int, int> histogram(const std::function<I(I)> &fun, const I &i, int l)
{
    I      j = truncInterval(i, l);
    double d = pow(2, l);

    std::map<int, int> H;

    for (double x = j.lower(); x < j.upper(); x += d) {
        I   z(x, x + d);
        I   w  = fun(z);
        int lr = lcb(w);
        H[lr]++;
    }

    return H;
}

/**
 * @brief Print the histogram as a csv file
 *
 * @param filename
 * @param H
 */
void csvfile(const std::string &filename, const std::map<int, int> &H)
{
    std::ofstream csvfile;
    csvfile.open(filename.c_str());

    csvfile << "LSB,\tVALUES" << std::endl;
    for (auto r : H) {
        csvfile << r.first << ",\t" << r.second << std::endl;
    }
    csvfile.close();
}

/**
 * @brief Compute the number of cases in histogram H
 *
 * @param H
 * @return int total number of cases in H
 */
int cases(const std::map<int, int> &H)
{
    int c = 0;
    for (auto r : H) c += r.second;
    return c;
}

/**
 * @brief compute the precision needed to cover c (0..1) cases
 *
 * @param H the histogram to analyze
 * @param c between 0 and 1: 1 covers all cases, 0.999 covers most cases, etc.
 * @return int the precision
 */
int precision(const std::map<int, int> &H, double c)
{
    int tc  = cases(H);
    int l   = 0;
    int sum = 0;
    for (auto r : H) {
        double w = double(tc - sum) / tc;
        if (w >= c) {
            l = r.first;
        } else {
            return l;
        }
        sum += r.second;
    }
    return l;
}

/**
 * @brief mapping between input and output precision
 *
 * @param fun
 * @param i input interval
 * @param l -1..l précisions
 * @param cov
 * @return std::map<int, int> input -> output precision
 */
std::map<int, int> rmapping(const std::function<I(I)> &fun, const I &i, int l, double cov)
{
    std::map<int, int> M;
    for (int k = -1; k >= l; k--) {
        M[k] = precision(histogram(fun, i, k), cov);
    }
    return M;
}

/**
 * @brief analyze : fixpoint tester
 *
 * @param fun
 * @param i
 * @param l
 * @param hist
 */
void analyze(const std::string &msg, const std::function<I(I)> &fun, const I &i, int l, bool hist)
{
    I j = truncInterval(i, l);
    //    double delta = pow(2, l);
    I k = fun(j);

    std::cout << "\nTEST: lambda(i).(" << msg << "); interval: " << i << "; LSB: " << l << "; truncated interval: " << j
              << "; MSB: " << msb(j) << "; resulting interval: " << k << "; MSB: " << msb(k) << std::endl;

    std::map<int, int> R = histogram(fun, i, l);

    // compute the number of cases
    int tc = cases(R);

    if (hist) std::cout << "LSB \tNUM \tRATIO " << std::endl;
    int sum  = 0;
    int g999 = 0;
    int g99  = 0;
    int best = 0;
    for (auto r : R) {
        double w = double(tc - sum) / tc;
        if (w >= 1) {
            best = r.first;
        }
        if (w >= 0.999) {
            g999 = r.first;
        }
        if (w >= 0.99) {
            g99 = r.first;
        }
        if (hist) std::cout << r.first << '\t' << r.second << '\t' << w << std::endl;
        sum += r.second;
    }
    std::cout << "Cases: " << tc << "; MSB: " << msb(k) << "; best precision LSB: " << best
              << "; very good precision LSB (0.999): " << g999 << "; good precision LSB (0.99): " << g99 << std::endl;
}
