#pragma once

#include <boost/numeric/interval.hpp>
#include <iostream>

using namespace boost::numeric;
using namespace interval_lib;

using I = interval<double, policies<save_state<rounded_transc_std<double>>, checking_base<double>>>;

inline std::ostream& operator<<(std::ostream& file, const I& i)
{
    return file << '[' << i.lower() << ';' << i.upper() << ']';
}
