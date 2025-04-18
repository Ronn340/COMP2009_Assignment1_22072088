/*
 * Main.cpp
 *
 *  Created on: 1/03/2025
 *      Author: dongmo
 */

#include<iostream>
#include<string>

using namespace std;
#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"
#include "MonteCarloPlayer.h"
#include "HumanPlayer.h"
#include "NashGame.h"

int main() {
	srand(time(0));

	int boardSize = 5;
	cout << "Input the size of board:" << endl;
	cin >> boardSize;
	if (boardSize < 3)
		boardSize = 3;

	Board* board = new Board(boardSize);

	//Player* p1 = new HumanPlayer(1, "HUMAN_1 (Black)");
	//Player* p1 = new RandomPlayer(1, "RANDOM_1 (Black)");
	//Player* p1 = new SmartPlayer(1, "SMART_1 (Black)");
	Player* p1 = new MonteCarloPlayer(1, "MONTECARLO_1 (Black)");


	//Player* p2 = new HumanPlayer(-1, "SMARTPLAYER_2 (White)");
	//Player* p2 = new RandomPlayer(-1, "RANDOM_2 (White)");
	//Player* p2 = new SmartPlayer(-1, "SMART_2 (White)");
	Player* p2 = new MonteCarloPlayer(-1, "MONTECARLO_2 (White)");




	NashGame game(board, p1, p2);
	game.play();

	delete board;
	delete p1;
	delete p2;

	//	system("pause");
	return 0;
}

