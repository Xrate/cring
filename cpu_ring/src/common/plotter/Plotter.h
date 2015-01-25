#ifndef PLOTTER_H
#define PLOTTER_H
#include "../../global.h"

class Plotter
{
public:
	static void setUpPlotter(string dirName, size_t turns, size_t size, size_t num_steps);

	static void plot(string plot_name, size_t turn);
	static void plot(string plot_name, size_t start_turn, size_t last_turn);
	static void plotX(string plot_name, size_t start_turn, size_t last_turn);
	static void plotY(string plot_name, size_t start_turn, size_t last_turn);
private:
	static string dirName_;
	static size_t nTurns_;
	static size_t nParticles_;
	static size_t nSteps_;
};

#endif // PLOTTER_H
