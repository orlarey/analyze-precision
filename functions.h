#pragma once

#include <functional>
#include <map>
#include <string>
#include "interval.h"

/**
 * @brief retrieve an interval function from its name
 *
 * @param name : the name of the function
 * @return const std::function<I(I)>& : pointer to the corresponding function
 */
const std::function<I(I)>& name2function(const std::string& name);

/**
 * @brief print a list of all the defined functions
 *
 */
void listFunctions();
