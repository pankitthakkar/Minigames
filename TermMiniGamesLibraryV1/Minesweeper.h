#pragma once
//Minesweeper header for tests / integration
#include "Main.h"
#include <stdbool.h>

#define EASYSIZE 9	//got difficulties from wikipedia...
#define EASYMINE 10

#define MEDSIZE 16
#define MEDMINE 40

#define HARDSIZE 30
#define HARDMINE 99

#define MAXINPUT 30
#define MINE -2
#define UNINIT -1

typedef struct MinesweeperBoard {
	int rows;
	int columns;

	int numOfMines;
	int currentMines;

	int** currentBoard;
	int** filledBoard;

}MBoard;

void startGame(USER* inputUser);//actual game called by runMineSweeper

void RunMineSweeper(USER* inputUser);//this will be called in main and pass the user into it to save scores

MBoard initalizeBoard(int xWidth, int yHeight, int numOfMines);//initliaze board for new game

void printCurrentBoard(MBoard printBoard); //top simplify job later on

void printFinalBoard(MBoard printBoard);

int updateBoard(MBoard* currentBoard);//gets user choice, first goes to checkInput then updates and returns board

int updateBoardStub(MBoard* testBoard, int testRow, int testColumn);

int checkInput(MBoard gameBoard,int inputRow, int inputColumn);//checks input compared to current board and returns new board

void playerWin(USER* inputUser,int newScore);//updates user if socre is higher then returns choice of 0 error, 1 continue, 2 exit

void playerLose(MBoard* deleteBoard);//returns choice of 0 error, 1 continue, 2 exit

bool checkWin(MBoard inputBoard);

void deleteMBoard(MBoard* inputBoard);