#include "Plotter.h"
#include "fstream"

string Plotter::dirName_;
size_t Plotter::nTurns_;
size_t Plotter::nParticles_;
size_t Plotter::nSteps_;

void Plotter::setUp(OutDirConfig dirConfig)
{
	dirName_ = dirConfig.dirName;
	nTurns_ = dirConfig.turns;
	nParticles_ = dirConfig.particles;
	nSteps_ = dirConfig.steps;
}

void Plotter::plot(string plotName, size_t turn)
{
	plot(plotName, turn, turn);
}

void Plotter::plot(string plot_name, size_t start_turn, size_t last_turn)
{
	plotX(plot_name, start_turn, last_turn);
	plotY(plot_name, start_turn, last_turn);
}

void Plotter::plotX(string plot_name, size_t start_turn, size_t last_turn)
{
	auto pFile = ofstream(dirName_ + "\\" + plot_name + "X.plt", ofstream::out);

	pFile << "set terminal png medium size " << (last_turn - start_turn + 1) * 10000 << " " << 1000 << endl;
	pFile << "set output '" << plot_name << "X.png'" << endl << endl;

	pFile << "set autoscale fix" << endl << endl;

	pFile << "set xlabel 'S'" << endl;
	pFile << "set ylabel 'X'" << endl << endl;

	pFile << "set title 'Trajectory XOS'" << endl;
	pFile << "set grid" << endl << endl;

	pFile << "set style line 1 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'black'" << endl;
	pFile << "set style line 2 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'red'" << endl;
	pFile << "set style line 3 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'cyan'" << endl << endl;

	pFile << "filename(n) = sprintf(\"particles/%d.out\", n)" << endl << endl;

	size_t startRow = (start_turn - 1) * nSteps_ + 1;
	size_t finalRow = last_turn * nSteps_;

	pFile << "plot for [i=0:" << nParticles_ - 1 << "] filename(i) every ::" << startRow
		<< "::" << finalRow << " using 1:2 ls 1 title '', \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow
		<< " using 1:2     title '' ls 2 with lines, \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow
		<< " using 1:(-$2) title '' ls 2 with lines, \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow
		<< " using 1:3     title '' ls 3 with lines, \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow
		<< " using 1:(-$3) title '' ls 3 with lines, \\" << endl;

	pFile.close();
}

void Plotter::plotY(string plot_name, size_t start_turn, size_t last_turn)
{
	auto pFile = ofstream(dirName_ + "\\" + plot_name + "Y.plt", ofstream::out);

	pFile << "set terminal png medium size " << (last_turn - start_turn + 1) * 10000 << " " << 1000 << endl;
	pFile << "set output '" << plot_name << "Y.png'" << endl << endl;

	pFile << "set autoscale fix" << endl << endl;

	pFile << "set xlabel 'S'" << endl;
	pFile << "set ylabel 'Y'" << endl << endl;

	pFile << "set title 'Trajectory YOS'" << endl;
	pFile << "set grid" << endl << endl;

	pFile << "set style line 1 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'black'" << endl;
	pFile << "set style line 2 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'red'" << endl;
	pFile << "set style line 3 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'cyan'" << endl << endl;

	pFile << "filename(n) = sprintf(\"particles/%d.out\", n)" << endl << endl;

	size_t startRow = (start_turn - 1) * nSteps_ + 1;
	size_t finalRow = last_turn * nSteps_;

	pFile << "plot for [i=0:" << nParticles_ - 1 << "] filename(i) every ::" << startRow
		<< "::" << finalRow << " using 1:3 ls 1 title '', \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow 
		<< " using 1:4     title '' ls 2 with lines, \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow 
		<< " using 1:(-$4) title '' ls 2 with lines, \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow 
		<< " using 1:5     title '' ls 3 with lines, \\" << endl;
	pFile << "	 'ellipses.out' every ::" << startRow << "::" << finalRow 
		<< " using 1:(-$5) title '' ls 3 with lines, \\" << endl;

	pFile.close();
}

void Plotter::plotFreqMap()
{
}