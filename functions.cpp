#include "functions.h"

static std::map<std::string, std::function<I(I)>> gFunctions = {
    {"square", [](const I& i) { return square(i); }},
    {"sin", [](const I& i) { return sin(i); }},
    {"cos", [](const I& i) { return cos(i); }},
    {"tan", [](const I& i) { return tan(i); }},
    {"asin", [](const I& i) { return asin(i); }},
    {"acos", [](const I& i) { return acos(i); }},
    {"atan", [](const I& i) { return atan(i); }},
    {"sinh", [](const I& i) { return sinh(i); }},
    {"cosh", [](const I& i) { return cosh(i); }},
    {"tanh", [](const I& i) { return tanh(i); }},
    {"log", [](const I& i) { return log(i); }},
    {"exp", [](const I& i) { return exp(i); }},
    {"sqrt", [](const I& i) { return sqrt(i); }},
    {"abs", [](const I& i) { return abs(i); }},
    {"floor", [](const I& i) { return I(floor(i.lower()), floor(i.upper())); }},
    {"ceil", [](const I& i) { return I(ceil(i.lower()), ceil(i.upper())); }},
    {"identity", [](const I& i) { return i; }}

};

/**
 * @brief retrieve an interval function from its name
 *
 * @param name : the name of the function
 * @return const std::function<I(I)>& : pointer to the corresponding function
 */
const std::function<I(I)>& name2function(const std::string& name)
{
    auto p = gFunctions.find(name);
    if (p == gFunctions.end()) {
        return gFunctions["identity"];
    } else {
        return p->second;
    }
    return gFunctions[name];
}

void listFunctions()
{
    for (auto e : gFunctions) {
        std::cout << e.first << std::endl;
    }
}
