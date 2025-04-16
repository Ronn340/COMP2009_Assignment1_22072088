#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

using namespace std;

class RandomPlayer : public Player {
public:
	RandomPlayer(int t, string name = "RandomBot") :
		Player(t, name) {
	}
	bool getMove(Board* board, int&, int&);
};

bool RandomPlayer::getMove(Board* board, int& x, int& y)
{

	vector <Cell> emptyCells = board->getEmptyCells();
	int index = rand() % emptyCells.size();

	x = emptyCells[index].x;
	y = emptyCells[index].y;

	return true;
}

#endif // !RANDOMPLAYER_H
