//source for minesweeper game
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "Main.h"
#include "Minesweeper.h"
#define EASYSIZE 9	//got difficulties form wikipedia...
#define EASYMINE 10
#define MEDSIZE 16
#define MEDMINE 40
#define HARDSIZE 30
#define HARDMINE 99
#define MINE -2
#define UNINIT -1
//void RunMineSweeper(USER* inputUser) {//this will be called in main and pass the user into it to save scores
//
//}

MBoard initalizeBoard(const int xWidth, const int yHeight, int numOfMines) {//initliaze board for new game
	srand(time(NULL));
	int height;
	int width;
	MBoard newBoard = { 0 };
	newBoard.filledBoard = (int**)malloc(xWidth * sizeof(int*));
	for (int i = 0; i < yHeight; ++i) {
		newBoard.filledBoard[i] = (int*)malloc(yHeight * sizeof(int));
	}


	newBoard.currentBoard = (int**)malloc(xWidth * sizeof(int*));
	for (int i = 0; i < yHeight; ++i) {
		newBoard.currentBoard[i] = (int*)malloc(yHeight * sizeof(int));
	}

	newBoard.numOfMines = numOfMines;//set values for mines, and numbers later
	newBoard.width = xWidth; 
	newBoard.height = yHeight;
	
	for (int y = 0; y < newBoard.height; y++) {
		for (int x = 0; x < newBoard.height; x++) {
			newBoard.filledBoard[x][y] = UNINIT;//0 == uninitalized for count later
			newBoard.currentBoard[x][y] = UNINIT;
		}
	}
	while (newBoard.currentMines < newBoard.numOfMines) {// -1 == mine on spot
		height = rand() % newBoard.height;
		width = rand() % newBoard.width;
		if (0 != (newBoard.filledBoard[width][height])) {//if mine is already there skip and try again
			newBoard.filledBoard[width][height] = MINE;
			newBoard.currentMines++;
		}
	}
	/*
				Think this is how grid appears??
				 x-1		 x			 x+1
				 
		y-1		[x-1][y-1]	[x][y-1]	[x+1][y-1]

		y		[x-1][y]	[x][y]		[x+1][y]

		y+1		[x-1][y+1]	[x][y+1]	[x+1][y+1]

	*/
	for (int y = 0; y < newBoard.width; y++) {
		for (int x = 0; x < newBoard.height; x++) {
			if (MINE != newBoard.filledBoard[x][y]) {
				newBoard.filledBoard[x][y] = 0;//redundant but good in case
			}
			if ((MINE == newBoard.filledBoard[x][y - 1]) && MINE != newBoard.filledBoard[x][y]) {//up
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x - 1][y - 1]) && MINE != newBoard.filledBoard[x][y]) {//up and left
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x - 1][y]) && MINE != newBoard.filledBoard[x][y]) {//left
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x - 1][y + 1]) && MINE != newBoard.filledBoard[x][y]) {//down and left
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x][y + 1]) && MINE != newBoard.filledBoard[x][y]) {//down
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x + 1][y + 1]) && MINE != newBoard.filledBoard[x][y]) {//down and right
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x + 1][y]) && MINE != newBoard.filledBoard[x][y]) {//right
				newBoard.filledBoard[x][y]++;
			}
			if ((MINE == newBoard.filledBoard[x + 1][y - 1]) && MINE != newBoard.filledBoard[x][y]) {//up and right
				newBoard.filledBoard[x][y]++;
			}
		}
	}
	return newBoard;
}
/*
	Key for numbers on board
		[M] == (val = -2, MINE) spot is a mine (if I have time i'll make mines not surrounded by unknown squares uncover themselves)...
		[?] == (val = -1, UNINIT) unknown / not chosen yet
		[0] == (val = 0) no mines around it
		[1] == 1 mine around it
		[2] == 2 mines around it
		[3] == 3 mines around it
		[4] == 4 mines around it
		[5] == 5 mines around it
		[6] == 6 mines around it
		[7] == 7 mines around it
		[8] == 8 mines around it
*/
void printCurrentBoard(MBoard printBoard) {
	for (int i = 0; i < printBoard.width; i++) {
		printf("[%d]\t", i);
	}
	printf("\n\n");

	for (int y = 0; y < printBoard.height; y++) {
		printf("[%d]\t", y);
		for (int x = 0; x < printBoard.width; x++) {
			if (UNINIT == printBoard.currentBoard[x][y]) {
				printf("[?]\t");
			}
			//else if (0 == printBoard.currentBoard[x][y]) {
			//	printf("[0]\t");//just in case 0 is weird
			//}
			else{
				printf("[%d]\t", printBoard.currentBoard[x][y]);
			}

		}
	}
}
void printFinalBoard(MBoard printBoard) {
	for (int i = 0; i < printBoard.width; i++) {
		printf("[%d]\t", i);
	}
	printf("\n\n");

	for (int y = 0; y < printBoard.height; y++) {
		printf("[%d]\t", y);
		for (int x = 0; x < printBoard.width; x++) {
			if (MINE == printBoard.currentBoard[x][y]) {
				printf("[M]\t");
			}
			else if (UNINIT == printBoard.currentBoard[x][y]) {
				printf("[?]\t");
			}
			//else if (0 == printBoard.currentBoard[x][y]) {
			//	printf("[0]\t");//just in case 0 is weird
			//}
			else {
				printf("[%d]\t", printBoard.currentBoard[x][y]);
			}

		}
	}
}
//bool updateBoard(MBoard* currentBoard) {//gets user choice, first goes to checkInput then updates and returns board
//
//}
//
//bool checkInput(MBoard currentBoard) {//checks input compared to current board and returns new board
//
//}
//
//int playerWin(USER* inputUser,MBoard* deleteBoard) {//updates user if socre is higher then returns choice of 0 error, 1 continue, 2 exit
//
//}
//
//int playerLose(MBoard* deleteBoard) {//returns choice of 0 error, 1 continue, 2 exit
//
//}
//
//int restartScreen() {//restart screen seen after win or loss
//
//}
void deleteBoard(MBoard* deleteBoard) {
	for (int i = 0; i < deleteBoard->height; ++i) {
		free(deleteBoard->filledBoard[i]);
	}
	free(deleteBoard->filledBoard);

	for (int i = 0; i < deleteBoard->height; ++i) {
		free(deleteBoard->currentBoard[i]);
	}
	free(deleteBoard->currentBoard);
}