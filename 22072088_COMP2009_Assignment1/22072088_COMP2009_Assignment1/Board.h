/*
 * BaseBoard.h
 *
 *  Created on: 1/03/2025
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_
//testing
#include <vector>
#include <stack>

class Board {
private:
	int boardSize;
	int turn;
	int** grid;
	vector <Cell> emptyCells;
public:
	Board(int bs) {
		boardSize = bs;
		grid = new int* [boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = 0;

				emptyCells.push_back({ i , j });
			}
		turn = 1;
	}

	virtual ~Board() {

		for (int i = 0; i < boardSize; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(Board& cboard) {
		boardSize = cboard.getBoardSize();

		grid = new int* [boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				grid[i][j] = 0;

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = cboard.getGrid(i, j);
			}

		turn = cboard.getTurn();
		emptyCells = cboard.getEmptyCells();
	}

	int getBoardSize() {
		return boardSize;
	}

	int getGrid(int x, int y) {
		return grid[x][y];
	}

	int getTurn() {
		return turn;
	}

	vector<Cell> getEmptyCells() {
		return emptyCells;
	}

	int findVectorIndex(Cell target, vector<Cell> vector);
	
	void printVectorCells(vector<Cell> cells);

	void printStackCells(stack<Cell> cells);

	stack<Cell> getPerpendicularNeighbors(int playerType, int x, int y);

	stack<Cell> getNeighbors(int playerType, int x, int y);

	vector<Cell> depthFirstSearch(int x, int y);


	bool cellAt(vector<Cell> vector, Cell c);

	bool endPointsFound(vector<Cell> path, int playerType);

	bool validInput(int, int);

	bool addMove(int playerType, int x, int y);

	int checkWinningStatus(vector<Cell> path, int playerType) {
		if (endPointsFound(path, playerType))
			return playerType;
		else if (emptyCells.empty())
			return 999;
		else
			return 0;
	}

	int checkWinningStatus();


	void printBoard();
};

bool Board::validInput(int x, int y) {
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
		cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	return true;
}

bool Board::addMove(int playerType, int x, int y) {

	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	grid[x][y] = playerType;

	emptyCells.erase(emptyCells.begin() + findVectorIndex({ x, y }, emptyCells));

	turn = -1 * turn;
	return true;
}

void Board::printBoard() {
	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		if (j < 9)
			cout << j + 1 << "   ";
		else
			cout << j + 1 << "  ";
	}
	cout << endl;

	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}
	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		for (int k = 0; k < i; k++)
			cout << "  ";

		if (i < 9)
			cout << " " << i + 1 << " ";
		else
			cout << i + 1 << " ";

		for (int j = 0; j < boardSize; j++) {
			if (grid[i][j] == 0) {
				if (j == 0) {
					cout << "|   |";
				}
				else {
					cout << "   |";
				}
			}
			else if (grid[i][j] == 1) {
				if (j == 0) {
					cout << "| B |";
				}
				else {
					cout << " B |";
				}
			}
			else {
				if (j == 0) {
					cout << "| W |";
				}
				else {
					cout << " W |";
				}
			}
		}
		cout << endl;
	}

	for (int k = 0; k <= boardSize; k++)
		cout << "  ";

	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}

	cout << endl;
	cout << endl;
}

void Board::printVectorCells(vector<Cell> cells)
{
	cout << "Empty/DFS-path cells: " << endl;
	for (int i = 0; i < cells.size(); i++)
	{
		cout << i + 1 << ". (" << cells[i].x + 1 << ", " << cells[i].y + 1<< ")" << endl;
	}

	cout << endl;
}

void Board::printStackCells(stack<Cell> cells)
{
	int i = 1;

	while (!cells.empty())
	{
		cout << i++ <<". (" << cells.top().x + 1<< ", " << cells.top().y + 1<< ")" << endl;
		cells.pop();
	}
}


int Board::findVectorIndex(Cell target, vector<Cell> vector)
{
	int index = -1;

	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i].x == target.x && vector[i].y == target.y)
			return i;
	}
	return index;
}

int Board::checkWinningStatus()
{
	//black
		for (int x = 0, y = 0; y < boardSize; y++)
		{

			if(getGrid(x, y) == 1 && endPointsFound(depthFirstSearch(x, y), 1))
				return 1;
		}

	//white

		for (int x = 0, y = 0; x < boardSize; x++)
		{
			if (getGrid(x, y) == -1 && endPointsFound(depthFirstSearch(x, y), -1))
				return -1;
		}
	
		if (emptyCells.empty())
			return 999;

		return 0;
}


bool Board::endPointsFound(vector<Cell> path, int playerType)
{
	bool startPoint = false;
	bool endPoint = false;

	if (playerType == 1)
	{
		for (int i = 0; i < path.size(); i++)
		{
			if (path[i].x == 0)
				startPoint = true;
			if (path[i].x == boardSize - 1)
				endPoint = true;
		}
	}
	else 
	{
		for (int i = 0; i < path.size(); i++)
		{
			if (path[i].y == 0)
				startPoint = true;
			if (path[i].y == boardSize - 1)
				endPoint = true;
		}
	}

	if (startPoint && endPoint)
		return true;
	else
		return false;
}


stack<Cell> Board::getNeighbors(int playerType, int x, int y)
{
	stack<Cell> neighbors;

		if (y - 1 >= 0 && grid[x][y - 1] == playerType)								// left
			neighbors.push({ x, y - 1 });

		if (x - 1 >= 0 && grid[x - 1][y] == playerType)								//top
			neighbors.push({ x - 1, y });

		if(x - 1 >= 0 && y + 1 < boardSize && grid[x - 1][y + 1] == playerType)		//top right
			neighbors.push({ x - 1, y + 1 });					

		if (y + 1 < boardSize && grid[x][y + 1] == playerType)						//right
			neighbors.push({ x, y + 1 });
	
		if (x + 1 < boardSize && grid[x + 1][y] == playerType)						//bottom
			neighbors.push({ x + 1, y });
		
		if (x + 1 < boardSize && y - 1 >= 0 && grid[x + 1][y - 1] == playerType)	//bottome left
			neighbors.push({ x + 1, y - 1 });							

		return neighbors;
	
}

stack<Cell> Board::getPerpendicularNeighbors(int playerType, int x, int y)
{
	stack<Cell> neighbors;

	if (playerType == -1)			//White or player2
	{
		if (y - 1 >= 0 && grid[x][y - 1] == playerType)
			neighbors.push({ x, y - 1 });

		if (y + 1 < boardSize && grid[x][y + 1] == playerType)
			neighbors.push({ x, y + 1 });

	}
	else							//Black or player 1
	{
		if (x - 1 >= 0 && grid[x - 1][y] == playerType)
			neighbors.push({ x - 1, y });

		if (x + 1 < boardSize && grid[x + 1][y] == playerType)
			neighbors.push({ x + 1, y });

	}
	return neighbors;

}

vector<Cell> Board::depthFirstSearch(int x, int y) 
{
	vector<Cell> visited;
	stack<Cell> toBeVisited;

	toBeVisited.push({ x, y });

	while (!toBeVisited.empty())
	{
		Cell currentCell = toBeVisited.top();
		toBeVisited.pop();

		if (!cellAt(visited, currentCell))
			visited.push_back(currentCell);

		stack<Cell> neighborsOfCurrent = getNeighbors(grid[x][y], currentCell.x, currentCell.y);
		// ==== CHANGE HERE FOR TASK 3 AND 5 ====
		
		while (!neighborsOfCurrent.empty())
		{
			if (!cellAt(visited, neighborsOfCurrent.top()))
				toBeVisited.push(neighborsOfCurrent.top());

			neighborsOfCurrent.pop();
		}
	}
	return visited;
}

bool Board::cellAt(vector<Cell> vector, Cell target)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i].x == target.x && vector[i].y == target.y)
			return true;
	}
	return false;
}







#endif /* BOARD_H_ */
