#include "Plotter.h"
#include "fstream"

DataProps Plotter::config;

void Plotter::setUp(DataProps dirConfig)
{
	config.dirName = dirConfig.dirName;
	config.turns = dirConfig.turns;
	config.particles = dirConfig.particles;
	config.steps = dirConfig.steps;
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
	auto pFile = ofstream(config.dirName + "\\" + plot_name + "X.plt", ofstream::out);

    pFile << "set terminal png medium size " << (last_turn - start_turn + 1) * 2000 << "," << 1000 << endl;
    pFile << "set output '" << plot_name << "X.png'" << endl << endl;

    pFile << "set autoscale fix" << endl << endl;

    pFile << "set xlabel 'S'" << endl;
    pFile << "set xtics 15" << endl;
    pFile << "set mxtics 5" << endl;
    pFile << "set ylabel 'X'" << endl << endl;

    pFile << "set title 'Trajectory XOS'" << endl;
    pFile << "set grid" << endl << endl;

    pFile << "set style line 1 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'black'" << endl;
    pFile << "set style line 2 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'red'" << endl;
    pFile << "set style line 3 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'cyan'" << endl << endl;

    pFile << "filename(n) = sprintf(\"particles/%d.out\", n)" << endl << endl;

	size_t startRow = (start_turn - 1) * config.steps + 1;
	size_t finalRow = last_turn * config.steps;

	pFile << "plot for [i=0:" << config.particles - 1 << "] filename(i) every ::" << startRow
        << "::" << finalRow << " using 1:2 ls 1 title '', \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow
        << " using 1:2     title '' ls 2 with lines, \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow
        << " using 1:(-$2) title '' ls 2 with lines, \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow
        << " using 1:3     title '' ls 3 with lines, \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow
        << " using 1:(-$3) title '' ls 3 with lines, \\" << endl;

    pFile.close();
}

void Plotter::plotY(string plot_name, size_t start_turn, size_t last_turn)
{
	auto pFile = ofstream(config.dirName + "\\" + plot_name + "Y.plt", ofstream::out);

    pFile << "set terminal png medium size " << (last_turn - start_turn + 1) * 2000 << "," << 1000 << endl;
    pFile << "set output '" << plot_name << "Y.png'" << endl << endl;

    pFile << "set autoscale fix" << endl << endl;

    pFile << "set xlabel 'S'" << endl;
    pFile << "set xtics 15" << endl;
    pFile << "set mxtics 5" << endl;
    pFile << "set ylabel 'Y'" << endl << endl;

    pFile << "set title 'Trajectory YOS'" << endl;
    pFile << "set grid" << endl << endl;

    pFile << "set style line 1 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'black'" << endl;
    pFile << "set style line 2 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'red'" << endl;
    pFile << "set style line 3 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'cyan'" << endl << endl;

    pFile << "filename(n) = sprintf(\"particles/%d.out\", n)" << endl << endl;

	size_t startRow = (start_turn - 1) * config.steps + 1;
	size_t finalRow = last_turn * config.steps;

	pFile << "plot for [i=0:" << config.particles - 1 << "] filename(i) every ::" << startRow
        << "::" << finalRow << " using 1:3 ls 1 title '', \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow 
        << " using 1:4     title '' ls 2 with lines, \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow 
        << " using 1:(-$4) title '' ls 2 with lines, \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow 
        << " using 1:5     title '' ls 3 with lines, \\" << endl;
    pFile << "     'ellipses.out' every ::" << startRow << "::" << finalRow 
        << " using 1:(-$5) title '' ls 3 with lines, \\" << endl;

    pFile.close();
}

void Plotter::plotFreqMap()
{
	auto pFile = ofstream(config.dirName + "\\" + "freqMap" + ".plt", ofstream::out);

    pFile << "set terminal png medium size " << 2000 << "," << 2000 << endl;
    pFile << "set output '" << "freqMap.png'" << endl << endl;

    pFile << "set autoscale fix" << endl << endl;

    pFile << "set xlabel 'Qy'" << endl;
    pFile << "set ylabel 'Qx'" << endl << endl;

    pFile << "set title 'Frequency Map'" << endl;
    pFile << "set grid" << endl << endl;

    pFile << "set style line 1 lt 2 lw 2 pt 1 ps 0.25 linecolor rgb 'black'" << endl;

    pFile << "filename = 'freqMap.out'" << endl << endl;

    pFile << "plot filename using 1:2 ls 1 title ''" << endl;

    pFile.close();
}