#pragma once
//Minesweeper header for tests / integration
#define MAXBOARD 52//fixes compilation issue
typedef struct MinesweeperBoard {
	int height;
	int width;

	int numOfMines;
	int currentMines;

	int currentBoard[MAXBOARD][MAXBOARD];
	int filledBoard[MAXBOARD][MAXBOARD];

}MBoard;
//void RunMineSweeper(USER* inputUser);//this will be called in main and pass the user into it to save scores

MBoard initalizeBoard(int xWidth, int yHeight, int numOfMines);//initliaze board for new game

void printCurrentBoard(MBoard printBoard); //top simplify job later on

void printFinalBoard(MBoard printBoard);

//bool updateBoard(MBoard* gameBoard);//gets user choice, first goes to checkInput then updates and returns board
//
//bool checkInput(MBoard gameBoard);//checks input compared to current board and returns new board
//
//int playerWin(USER* inputUser,MBoard* deleteBoard);//updates user if socre is higher then returns choice of 0 error, 1 continue, 2 exit
//
//int playerLose(MBoard* deleteBoard);//returns choice of 0 error, 1 continue, 2 exit
//
//int restartScreen();//restart screen seen after win or loss