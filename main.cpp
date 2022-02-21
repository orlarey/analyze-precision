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
//#include "draw.h"
#include "functions.h"

//#include "pbPlots.h"
//#include "supportLib.h"

#include "print.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        listFunctions();
    } else if (argc != 5) {
        std::cout << argv[0] << " function lsb lo hi" << std::endl;
    } else {
        // analyze(argv[1], name2function(argv[1]), I(atof(argv[3]), atof(argv[4])), atoi(argv[2]), false);
        // compute histogram
        auto        fun = name2function(argv[1]);
        std::string msg = argv[1];
        int         lsb = atoi(argv[2]);
        I           i(atof(argv[3]), atof(argv[4]));

        auto H = histogram(fun, i, lsb);
        gnuplotfile(msg, lsb, i.lower(), i.upper(), H);
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