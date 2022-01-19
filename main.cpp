/*
#include <algorithm>
#include <boost/numeric/interval.hpp>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>
*/
#include "analyze.h"
//#include "truncate.h"

int main()
{
    int lsb = -18;
    {
        auto        fun = [](I i) { return square(sin(i)); };
        std::string msg = "square(sin(i))";
        analyze(msg, fun, I(0.1, M_PI), lsb, false);
    }
    //
    {
        auto        fun = [](I i) { return 1.0 / sin(i); };
        std::string msg = "1.0 / sin(i)";
        analyze(msg, fun, I(0.1, M_PI), lsb, false);
    }
    //
    {
        auto        fun = [](I i) { return atan(i * 10.0); };
        std::string msg = "atan(i * 10.0)";
        analyze(msg, fun, I(-1, 1), lsb, false);
    }
    //
    {
        auto        fun = [](I i) { return i - pow(i, 3.0); };
        std::string msg = "i - pow(i, 3.0)";
        analyze(msg, fun, I(-1, 1), lsb, false);
    }
    //
    {
        auto        fun = [](I i) { return cos(i - M_PI_2); };
        std::string msg = "cos(i-PI/2)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return sin(i + M_PI_2); };
        std::string msg = "sin(i + M_PI_2)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return tan(i); };
        std::string msg = "tan(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return acos(i); };
        std::string msg = "acos(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return asin(i); };
        std::string msg = "asin(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return atan(i); };
        std::string msg = "atan(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return atan(i); };
        std::string msg = "atan(i)";
        I           i(-10, 10);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](I i) { return cos(i); };
        std::string msg = "cos(i)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return tan(i); };
        std::string msg = "tan(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return tan(i); };
        std::string msg = "tan(i)";
        I           i(-1.5, 1.5);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return exp(i); };
        std::string msg = "exp(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return log(i); };
        std::string msg = "log(i)";
        I           i(0.001, 100);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return sqrt(i); };
        std::string msg = "sqrt(i)";
        I           i(0.001, 8);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return abs(i); };
        std::string msg = "abs(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return i; };
        std::string msg = "i";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return i * 8.0; };
        std::string msg = "i*8.0";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return i / 8.0; };
        std::string msg = "i/8.0";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(1, 2);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(-1, -1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](I i) { return sin(i); };
        std::string msg = "sin(i)";
        int         lsb = -18;
        I           i(0, M_PI * 2.0);
        analyze(msg, fun, i, lsb, true);
    }

    return 0;
}

/*
acos Primitive
asin Primitive
atan Primitive
atan2 Primitive
cos Primitive
sin Primitive
tan Primitive
exp Primitive
log Primitive
log10 Primitive
pow Primitive
sqrt Primitive
abs Primitive
min Primitive
max Primitive
fmod Primitive
remainder Primitive
floor Primitive
ceil Primitive
rint Primitive
*/