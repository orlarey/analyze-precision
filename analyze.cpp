#include <iostream>
#include <map>

#include "analyze.h"
#include "truncate.h"

/**
 * @brief analyze : fixpoint tester
 *
 * @param fun
 * @param i
 * @param l
 * @param hist
 */
void analyze(const std::string& msg, const std::function<I(I)>& fun, I i, int l, bool hist)
{
    I      j     = truncInterval(i, l);
    double delta = pow(2, l);
    I      k     = fun(j);

    std::cout << "\nTEST: lambda(i).(" << msg << "); interval: " << i << "; LSB: " << l << "; truncated interval: " << j
              << "; MSB: " << msb(j) << "; resulting interval: " << k << "; MSB: " << msb(k) << std::endl;

    std::map<int, int> R;

    int cases = 0;
    for (double x = j.lower(); x < j.upper(); x += delta) {
        cases++;
        I   z(x, x + delta);
        I   w  = fun(z);
        int lr = lcb(w);
        R[lr]++;
    }

    if (hist) std::cout << "LSB \tNUM \tRATIO " << std::endl;
    int sum  = 0;
    int g999 = 0;
    int g99  = 0;
    int best = 0;
    for (auto r : R) {
        double w = double(cases - sum) / cases;
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
    std::cout << "Cases: " << cases << "; MSB: " << msb(k) << "; best precision LSB: " << best
              << "; very good precision LSB (0.999): " << g999 << "; good precision LSB (0.99): " << g99 << std::endl;
}
