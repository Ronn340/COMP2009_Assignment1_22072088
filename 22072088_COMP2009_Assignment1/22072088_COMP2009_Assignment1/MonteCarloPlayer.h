#ifndef MONTECARLOPLAYER_H
#define MONTECARLOPLAYER_H

class MonteCarloPlayer : public Player {
public:

	MonteCarloPlayer(int t, string name = "MonteCarlo") :
		Player(t, name) {}

	bool getMove(Board* board, int& x, int& y);
	double simulation(Board board);
	double expansion(Board board, int player);

};


bool MonteCarloPlayer::getMove(Board* board, int& x, int& y)
{
	priority_queue <Cell> moves;

	vector <Cell> emptyCells = board->getEmptyCells();

	for (Cell cell : emptyCells)
	{
		int i = cell.x;
		int j = cell.y;

		Board tempboard(*board);
		tempboard.addMove(type, i, j);

		if (tempboard.checkWinningStatus(tempboard.depthFirstSearch(i, j), type) == type)
		{
			x = i;
			y = j;
			return true;
		}

		double winAverage = simulation(tempboard);
		Cell c(i, j, winAverage);

		moves.push(c);
	}

	printPriorityQueue(moves);

	x = moves.top().x;
	y = moves.top().y;
	return true;
}

double MonteCarloPlayer::simulation(Board board)
{
	int times = 1000;
	double wins = 0.0;

	for (int i = 0; i < times; i++)
	{
		Board tempboard(board);
		int player = (type == 1) ? -1 : 1;
		wins += expansion(tempboard, player);
	}

	return wins/((double)times);
}

double MonteCarloPlayer::expansion(Board board, int player)
{
	int gameWinner = board.checkWinningStatus();

	if (gameWinner == type)
		return 1.0;

	else if (gameWinner != 0)
		return 0.0;

	vector <Cell> emptyCells = board.getEmptyCells();
	int index = rand() % emptyCells.size();

	board.addMove(player, emptyCells[index].x, emptyCells[index].y);

	player = (player == 1) ? -1 : 1;

	return expansion(board, player);	
}




#endif // !MONTECARLOPLAYER_H
