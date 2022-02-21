#pragma once

//#include <functional>
#include <map>
#include <string>
//#include "interval.h"

/**
 * @brief Print the histogram as a csv file
 *
 * @param filename
 * @param H
 */
void csvfile(std::string filename, const std::map<int, int> &H);

/**
 * @brief Print the histogram as a gnuplot file
 *
 * @param filename
 * @param H
 */
void gnuplotfile(std::string function, int lsb, double lo, double hi, const std::map<int, int> &H);
