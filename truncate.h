#pragma once

#include "interval.h"

double ipart(double x);
double dpart(double x);
double truncinf(double x, int l);
double truncsup(double x, int l);
I      truncInterval(const I& i, int l);

int lcb(double x, double y);
int lcb(const I& i);

int msb(double x);
int msb(const I& i);
