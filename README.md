[![C/C++ CI](https://github.com/orlarey/analyze-precision/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/orlarey/analyze-precision/actions/workflows/c-cpp.yml)

# analyze-precision
Analyze fix-point precision for unary functions

This program allows, for a given unary function, to explore the relations between the fixed point format of the argument, taken in a given range of values, and the fixed point format of the result.

# Example of analysis

Analyze the function `[](I i) { return sin(i); }` in the interval `I(0, M_PI*2.0)` with a LSB precision of `-18`:
	    
	auto        fun = [](I i) { return sin(i); };
	std::string msg = "sin(i)";
	int         lsb = -18;
	I		    i(0, M_PI*2.0);
	analyze(msg, fun, i, lsb, false);

The execution will produce:

	TEST: lambda(i).(sin(i)); interval: [0;6.28319]; LSB: -18; truncated interval: [0;6.28319]; MSB: 3; resulting interval: [-1;1]; MSB: 1

	Cases: 1647100; MSB: 1; best precision LSB: -39; very good precision LSB (0.999): -27; good precision LSB (0.99): -23

This result indicates that a LSB of -39 is required for all results to have optimal accuracy, but that with a LSB of -27, we still have 99.9% of results that have optimal accuracy.

It is also possible to ask for the histogram of the number of results per LSB precision by using `analyze(msg, fun, i, lsb, true);`:

	LSB     NUM     RATIO 
	-39     1       1
	-37     1       0.999999
	-36     3       0.999999
	-35     4       0.999997
	-34     8       0.999995
	-33     16      0.99999
	-32     32      0.99998
	-31     64      0.999961
	-30     128     0.999922
	-29     256     0.999844
	-28     512     0.999689
	-27     1024    0.999378
	-26     2048    0.998756
	-25     4096    0.997513
	-24     8193    0.995026
	-23     16394   0.990052
	-22     32842   0.980098
	-21     66147   0.960159
	-20     136300  0.919999
	-19     330455  0.837248
	-18     524286  0.63662
	-17     262145  0.318311
	-16     131073  0.159155
	-15     65536   0.0795774
	-14     32768   0.0397887
	-13     16384   0.0198944
	-12     8192    0.00994718
	-11     4096    0.00497359
	-10     2048    0.00248679
	-9      1024    0.0012434
	-8      512     0.000621699
	-7      256     0.000310849
	-6      128     0.000155425
	-5      64      7.77123e-05
	-4      32      3.88562e-05
	-3      16      1.94281e-05
	-2      8       9.71404e-06
	-1      4       4.85702e-06
	0       4       2.42851e-06

