/*
 * HumanPlayer.h
 *
 *  Created on: 1/03/2025
 *      Author: dongmo
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

using namespace std;

class HumanPlayer : public Player {
public:
	HumanPlayer(int t, string name = "Human") :
		Player(t, name) {
	}
	bool getMove(Board*, int&, int&);
};

bool HumanPlayer::getMove(Board* board, int& x, int& y) {
	bool flag = false;
	int bs = board->getBoardSize();

	while (!flag) {
		cout << "Input row and column (x, y) between 1 to " << bs << " for "
			<< name << " player:" << endl;
		int row, col;
		cin >> row >> col;
		x = row - 1;
		y = col - 1;
		flag = board->validInput(x, y);
		if (flag == false)
			cout << "Invalid input! Please input again." << endl;
	}


	//cout << "Neighbors at (" << x + 1 << ", " << y + 1 << "): " << endl;
 	//board->printStackCells(board->getNeighbors(type, x, y));				//TESTING FOR GETNEIGHBORS()
	return true;
}

#endif /* HUMANPLAYER_H_ */
