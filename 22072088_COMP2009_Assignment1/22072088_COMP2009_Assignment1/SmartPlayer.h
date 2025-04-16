#ifndef SMARTPLAYER_H
#define SMARTPLAYER_H

#include <queue>		//priority_queue
#include <algorithm>    // std::random_shuffle


using namespace std;

class SmartPlayer : public Player {
public:

	SmartPlayer(int t, string name = "SmartBot") :
		Player(t, name) {
	}
	int steps;

	bool getMove(Board*, int&, int&);

	double minMove(Board board);
	double maxMove(Board board);

};

void printPriorityQueue(priority_queue<Cell> moves) {
	cout << "Priority Queue Contents: " << endl;
	while (!moves.empty()) {
		Cell c = moves.top();
		cout << "(" << c.x + 1<< ", " << c.y + 1 << ") -> " << c.heuristic << "\n";
		moves.pop();
	}
}

bool SmartPlayer::getMove(Board* board, int& x, int& y) {

	priority_queue <Cell> moves;
	vector <Cell> emptyCells = board->getEmptyCells();
	random_shuffle(emptyCells.begin(), emptyCells.end());

	if (emptyCells.empty())
		return false;

	steps = 10000;

	for (Cell cell : emptyCells)
	{
		int i = cell.x;
		int j = cell.y;

		Board tempboard(*board);
		tempboard.addMove(type, i, j);

		int gameWinner = tempboard.checkWinningStatus(tempboard.depthFirstSearch(i, j), type);
		if (gameWinner == type)
		{
			x = i;
			y = j;
			return true;
		}

		double minUtility = minMove(tempboard);
		Cell c(i, j, minUtility);
		moves.push(c);
	}

	printPriorityQueue(moves);

	if (moves.size() > 0)
	{
		x = moves.top().x;
		y = moves.top().y;

		cout << moves.size() << " MiniMax Utility = " << moves.top().heuristic
			<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}
	return true;
}

double SmartPlayer::minMove(Board board)
{
	vector <Cell> emptyCells = board.getEmptyCells();
	if (emptyCells.empty() || steps <= 0)
		return -0.01;

	random_shuffle(emptyCells.begin(), emptyCells.end());

	double minUtility = 2;

	for (Cell cell : emptyCells)
	{
		int i = cell.x;
		int j = cell.y;

		Board tempboard(board);
		int player = (type == -1) ? 1 : -1;
		tempboard.addMove(player, i, j);

		int gameWinner = tempboard.checkWinningStatus(tempboard.depthFirstSearch(i, j), tempboard.getGrid(i, j));
		if (gameWinner != 0)
		{
			if (gameWinner == type)
				return 1;
			else
				return -1;
		}

		double utility;
		utility = maxMove(tempboard);
		

		if (utility < minUtility)
			minUtility = utility;
	}

	steps--;
	return minUtility;
}

double SmartPlayer::maxMove(Board board)
{
	vector <Cell> emptyCells = board.getEmptyCells();
	if (emptyCells.empty()|| steps <= 0)
		return 0.01;

	random_shuffle(emptyCells.begin(), emptyCells.end());

	double maxUtility = -2;

	for (Cell cell : emptyCells)
	{
		int i = cell.x;
		int j = cell.y;

		Board tempboard(board);
		tempboard.addMove(type, i, j);

		int gameWinner = tempboard.checkWinningStatus(tempboard.depthFirstSearch(i, j), tempboard.getGrid(i, j));
		if (gameWinner != 0)
		{
			if (gameWinner == type)
				return 1;
			else
				return -1;
		}

		double utility;
		utility= minMove(tempboard);
	
		if (utility > maxUtility)
			maxUtility = utility;
	}

	steps--;
	return maxUtility;
}
#endif // !SMARTPLAYER_H
