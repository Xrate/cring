#pragma once

#include "global.h"
#include "common/DataProps.h"

class FreqAnalyzer
{
public:
    static void setUp(DataProps dirConfig);
    static void print();
    static void calculate();
private:
    friend static void readParticleTraj(size_t iP, double* inX, double* inY);
	static DataProps config;
    static vector<double> Qx;
    static vector<double> Qy;
};
