#pragma once

#include "global.h"
#include <common/DataProps.h>

class Plotter
{
public:
    static void setUp(DataProps dirConfig);

    static void plot(string plot_name, size_t turn);
    static void plot(string plot_name, size_t start_turn, size_t last_turn);
    static void plotX(string plot_name, size_t start_turn, size_t last_turn);
    static void plotY(string plot_name, size_t start_turn, size_t last_turn);
    static void plotFreqMap();
private:
	static DataProps config;
};
