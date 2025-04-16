/*
 * HexGame.h
 *
 *  Created on: 1/03/2025
 *      Author: dongmo
 */

#ifndef NASHGAME_H_
#define NASHGAME_H_

class NashGame {
private:
	Board* board;
	Player* player[2];
public:
	NashGame(Board* b, Player* p1, Player* p2) {
		board = b;
		player[0] = p1;
		player[1] = p2;
	}

	void play();
};

void NashGame::play() {
	int won = 0;
	board->printBoard();

	while (!won) {

		int playerType = board->getTurn();
		int playerIndex = (playerType == player[0]->getType()) ? 0 : 1;
		int x = -1;
		int y = -1;

		if (!player[playerIndex]->getMove(board, x, y)) {
			cout << "No available move" << endl;
			return;
		}

		cout << player[playerIndex]->getPlayerName() << " plays " << " ("
			<< x + 1 << ", " << y + 1 << "):" << endl;

		if (!board->addMove(playerType, x, y))
			return;

		board->printVectorCells(board->depthFirstSearch(x, y));

		board->printBoard();
		won = board->checkWinningStatus();
		if (won == playerType)
			cout << player[playerIndex]->getPlayerName() << " player wins!" << endl;
		else if (won == 999)
			cout << "DRAW (This should only print when win condition is straight)" << endl;

	}
}

#endif /* NASHGAME_H_ */
