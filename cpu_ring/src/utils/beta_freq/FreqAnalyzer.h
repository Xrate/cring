#pragma once

#include "global.h"
#include "utils/DataProps.h"

class FreqAnalyzer
{
public:
    static void setUp(DataProps dirConfig);
    static void print();
    static void calculate();

private:
	static DataProps config;
    static vector<double> Qx;
    static vector<double> Qy;
};
