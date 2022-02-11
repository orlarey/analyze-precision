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
#include <sstream>

#include "analyze.h"
#include "draw.h"
#include "functions.h"

#include "pbPlots.h"
#include "supportLib.h"

//#include "truncate.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        listFunctions();
    } else if (argc != 5) {
        std::cout << argv[0] << " function lsb lo hi" << std::endl;
    } else {
        analyze(argv[1], name2function(argv[1]), I(atof(argv[3]), atof(argv[4])), atoi(argv[2]), false);
        // compute histogram
        auto        fun = name2function(argv[1]);
        std::string msg = argv[1];
        int         lsb = atoi(argv[2]);
        I           i(atof(argv[3]), atof(argv[4]));

        auto H = histogram(fun, i, lsb);
        // and generate csv files
        std::stringstream fname1, fname1b;
        fname1 << msg << '_' << lsb << '_' << i.lower() << '-' << i.upper() << "_histogram.csv";
        csvfile(fname1.str(), H);
        fname1b << msg << '_' << lsb << '_' << i.lower() << '-' << i.upper() << "_histogram.png";
        plotfile(fname1b.str(), H);
        //
        std::stringstream fname2, fname2b;
        fname2 << msg << '_' << lsb << '_' << i.lower() << '-' << i.upper() << "_reverse.csv";
        fname2b << msg << '_' << lsb << '_' << i.lower() << '-' << i.upper() << "_reverse.png";
        auto M = rmapping(fun, i, lsb, 0.999);
        csvfile(fname2.str(), M);
        plotfile(fname2b.str(), M);
    }

#if 0
    int lsb = -18;
    {
        auto        fun = [](const I& i) { return square(sin(i)); };
        std::string msg = "square(sin(i))";
        analyze(msg, fun, I(0.1, M_PI), lsb, false);
    }
    //
    {
        auto        fun = [](const I& i) { return 1.0 / sin(i); };
        std::string msg = "1.0 / sin(i)";
        analyze(msg, fun, I(0.1, M_PI), lsb, false);
    }
    //
    {
        auto        fun = [](const I& i) { return atan(i * 10.0); };
        std::string msg = "atan(i * 10.0)";
        analyze(msg, fun, I(-1, 1), lsb, false);
    }
    //
    {
        auto        fun = [](const I& i) { return i - pow(i, 3.0); };
        std::string msg = "i - pow(i, 3.0)";
        analyze(msg, fun, I(-1, 1), lsb, false);
    }
    //
    {
        auto        fun = [](const I& i) { return cos(i - M_PI_2); };
        std::string msg = "cos(i-PI/2)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return sin(i + M_PI_2); };
        std::string msg = "sin(i + M_PI_2)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return tan(i); };
        std::string msg = "tan(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return acos(i); };
        std::string msg = "acos(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return asin(i); };
        std::string msg = "asin(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return atan(i); };
        std::string msg = "atan(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return atan(i); };
        std::string msg = "atan(i)";
        I           i(-10, 10);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }
    {
        auto        fun = [](const I& i) { return cos(i); };
        std::string msg = "cos(i)";
        I           i(0, 2.0 * M_PI);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return tan(i); };
        std::string msg = "tan(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return tan(i); };
        std::string msg = "tan(i)";
        I           i(-1.5, 1.5);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return exp(i); };
        std::string msg = "exp(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return log(i); };
        std::string msg = "log(i)";
        I           i(0.001, 100);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return sqrt(i); };
        std::string msg = "sqrt(i)";
        I           i(0.001, 8);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return abs(i); };
        std::string msg = "abs(i)";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return i; };
        std::string msg = "i";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return i * 8.0; };
        std::string msg = "i*8.0";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return i / 8.0; };
        std::string msg = "i/8.0";
        I           i(-1, 1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(1, 2);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(-1, -1);
        analyze(msg, fun, i, lsb, false);
    }

    {
        auto        fun = [](const I& i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(0, M_PI * 2.0);
        analyze(msg, fun, i, lsb, true);
    }

    {
        auto        fun = [](const I& i) { return sin(i); };
        std::string msg = "sin(i)";
        I           i(0, M_PI * 2.0);
        auto        H = histogram(fun, i, lsb);
        csvfile("sin-18-histogram.csv", H);
        auto M = rmapping(fun, i, lsb, 0.999);
        csvfile("sin-18-reverse.csv", M);
    }

    {
        auto        fun = [](const I& i) { return atan(i); };
        std::string msg = "atan(i)";
        I           i(-10, 10);
        auto        H = histogram(fun, i, lsb);
        csvfile("atan-18-histogram.csv", H);
        auto M = rmapping(fun, i, lsb, 0.999);
        csvfile("atan-18-reverse.csv", M);
    }
#endif

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