#pragma once

#include <functional>
#include <string>

#include "interval.h"

/**
 * @brief analyze : analyze the relation between the argument and the result precision
 *
 * @param msg description of the unary function
 * @param fun unary function on intervals
 * @param i argument interval
 * @param l lsb precision
 * @param hist true, print histogram
 */
void analyze(const std::string& msg, const std::function<I(I)>& fun, I i, int l, bool hist);
