#pragma once

#include <functional>
#include <map>
#include <string>
#include "interval.h"

/**
 * @brief compute the precision histogram according to an interval i and a precision l
 *
 * @param fun unary function on intervals
 * @param i argument interval
 * @param l argument precision (lsb)
 * @return std::map<int, int> precision histogram
 */
std::map<int, int> histogram(const std::function<I(I)> &fun, const I &i, int l);

/**
 * @brief mapping between input and output precision
 *
 * @param fun
 * @param i input interval
 * @param l -1..l précisions
 * @param cov
 * @return std::map<int, int> input -> output precision
 */
std::map<int, int> rmapping(const std::function<I(I)> &fun, const I &i, int l, double cov);

/**
 * @brief Print the histogram as a csv file
 *
 * @param filename
 * @param H
 */
void csvfile(std::string filename, const std::map<int, int> &H);

/**
 * @brief Compute the number of cases in histogram H
 *
 * @param H
 * @return int total number of cases in H
 */
int cases(const std::map<int, int> &H);

/**
 * @brief analyze : analyze the relation between the argument and the result precision
 *
 * @param msg description of the unary function
 * @param fun unary function on intervals
 * @param i argument interval
 * @param l argument precision (lsb)
 * @param hist true, print histogram
 */
void analyze(const std::string &msg, const std::function<I(I)> &fun, const I &i, int l, bool hist);
