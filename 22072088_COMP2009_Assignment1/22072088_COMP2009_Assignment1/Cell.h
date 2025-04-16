
#ifndef CELL_H
#define CELL_H

struct Cell {
	int x, y;
	double heuristic;

	Cell(int x, int y, double heuristic) 
		: x(x), y(y), heuristic(heuristic) {}

	Cell(int x, int y)
		: x(x), y(y), heuristic(0.0) {
	}


	bool operator<(const Cell& c)const
	{
		return heuristic < c.heuristic;
	}
};
#endif // !CELL_H
