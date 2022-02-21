#include "print.h"

#include <fstream>
//#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "interval.h"

/**
 * @brief Print the histogram as a csv file
 *
 * @param filename
 * @param H
 */
void csvfile(std::string filename, const std::map<int, int> &H)
{
    std::cout << "==>" << filename << std::endl;
    std::ofstream csvfile;
    csvfile.open(filename.c_str());

    csvfile << "LSB,\tVALUES" << std::endl;
    for (auto r : H) {
        csvfile << r.first << ",\t" << r.second << std::endl;
    }
    csvfile.close();
}

/**
 * @brief Print the histogram as gnuplot command
 *
 * @param function
 * @param lsb
 * @param lo
 * @param hi
 * @param H
 */
void gnuplotfile(std::string function, int lsb, double lo, double hi, const std::map<int, int> &H)
{
    int total = 0;
    for (auto r : H) total += r.second;

    // print the number of values precisely described by
    // each LSB
    int limit999  = int(total * 0.999);
    int limit990  = int(total * 0.990);
    int limit900  = int(total * 0.900);
    int pos100    = 0;
    int pos999    = 0;
    int pos990    = 0;
    int pos900    = 0;
    int remaining = total;
    for (auto r : H) {
        if (remaining == total) pos100 = r.first;
        if (remaining >= limit999) pos999 = r.first;
        if (remaining >= limit990) pos990 = r.first;
        if (remaining >= limit900) pos900 = r.first;
        remaining -= r.second;
    }

    std::cout << "set title '" << function << " function, input lsb=" << lsb << "; input range [" << lo << ".." << hi
              << "]'" << std::endl;
    std::cout << "set ylabel 'Percentage of the " << total << " results accurately represented'" << std::endl;
    std::cout << "set xlabel 'Output precision lsb' " << std::endl;
    std::cout << "set grid" << std::endl;

    std::cout << "set xtics " << pos100 << ",1,0" << std::endl;

    std::cout << "set arrow from " << pos999 << ",0 to " << pos999 << "," << 100 << " nohead linecolor 'red' "
              << std::endl;

    std::cout << "set arrow from " << pos990 << ",0 to " << pos990 << "," << 100 << " nohead linecolor 'red' "
              << std::endl;

    std::cout << "plot '-' with lines" << std::endl;
    std::cout << "#LSB\tVALUES" << std::endl;

    // print the number of values precisely described by
    // each LSB
    remaining = total;
    for (auto r : H) {
        std::cout << r.first << "\t" << 100.0 * double(remaining) / double(total) << "\t" << remaining << std::endl;
        remaining -= r.second;
    }
    // file.close();
}
