//source for minesweeper game
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Main.h"
#include "Minesweeper.h"

#define EASYSIZE 11	//got difficulties form wikipedia...
#define EASYMINE 10

#define MEDSIZE 18
#define MEDMINE 40

#define HARDSIZE 32
#define HARDMINE 99

#define MAXINPUT 30
#define MINE -2
#define UNINIT -1
void startGame(USER* inputUser) {
	printf("Enter one of the following options (case sensitive)\n");
	printf("EASY - Width 09, Height 09, 10 mines\n");
	printf("MEDIUM - Width 16, Height 16, 40 mines\n");
	printf("HARD - Width 16, Height 30, 99 mines\n");
	printf("CUSTOM - (up to max of) Width 30, Height 60, 1000 mines\n");
	bool loop = true;
	int inputWidth = 0;
	int inputHeight = 0;
	int inputMineNum = 0;
	while (true == loop) {
		printf("\nNew Game selected, select difficulty name:");
		char optionChoice[MAXINPUT];
		scanf_s("%s", optionChoice, MAXINPUT - 1);
		char newline = getc(stdin);//trailing newline?
		if (0 == strcmp("EASY",optionChoice)) {//set to easy and exit loop
			inputWidth = EASYSIZE;
			inputHeight = EASYSIZE;
			inputMineNum = EASYMINE;
			loop = false;
		}
		else if (0 == strcmp("MEDIUM", optionChoice)) {//set to med and exit loop
			inputWidth = MEDSIZE;
			inputHeight = MEDSIZE;
			inputMineNum = MEDMINE;
			loop = false;
		}
		else if (0 == strcmp("HARD", optionChoice)) {//set to hard and exit loop
			inputWidth = MEDSIZE;
			inputHeight = HARDSIZE;
			inputMineNum = HARDMINE;
			loop = false;
		}
		else if (0 == strcmp("CUSTOM", optionChoice)) {//ask for custom and continue if within bounds
			printf("enter options as: Width Height Mines\n:");

			printf("input width (max of 50):");
			scanf_s("%d", &inputWidth);
			char newline = getc(stdin);//trailing newline?

			printf("input height (max of 50):");
			scanf_s("%d", &inputHeight);
			newline = getc(stdin);//trailing newline?

			printf("input number of mines (max of 1000, or width * height):");
			scanf_s("%d", &inputMineNum);
			newline = getc(stdin);//trailing newline?

			if ((0 < inputWidth <= 50) && (0 < inputHeight <= 50) && (0 < inputMineNum <= 1000) && (inputMineNum < (inputWidth * inputHeight))) {
				loop = false;
			}
			else {
				fprintf(stderr, "\nERROR: Incorrect range of input, or input calculation error\nReturning to selection...\n");
			}
		}
		else {
			fprintf(stderr, "\nERROR, Unknown input\n");
		}
		
	}
	MBoard gameBoard = initalizeBoard(inputWidth, inputHeight, inputMineNum);
	deleteMBoard(&gameBoard);
}
void RunMineSweeper(USER* inputUser) {//this will be called in main and pass the user into it to save scores
	printf("Welcome to Minesweeper %s!\n",inputUser->username);
	printf("Current Highscore = %d\n\n", inputUser->minesweeper_highscore);

	printf("would you like to: \n");
	printf("A = start a new game\n");
	printf("B = view Rules / Help\n");
	printf("C = Exit\n");
	char Choice;
	scanf_s("%c", &Choice,1);
	char newline = getc(stdin);//trailing newline?
	switch (Choice) {
	case 'A':
		startGame(inputUser);
	}
}

MBoard initalizeBoard(int xWidth,int yHeight, int numOfMines) {//initliaze board for new game
	srand(time(NULL));
	
	MBoard newBoard = { 0 };
	int length = 0;
	newBoard.numOfMines = numOfMines;//set values for mines, and numbers later
	newBoard.currentMines = 0;
	newBoard.width = xWidth;
	newBoard.height = yHeight;
	//row = y
	//col = x
	//to find things in array = [(y * numCols) * x]
	int numRows = newBoard.height+2;
	int numCols = newBoard.width+2;
	newBoard.currentBoard = (int*)malloc(numRows * numCols * sizeof(int));
	newBoard.filledBoard = (int*)malloc(numRows * numCols * sizeof(int));
	//error at (24,2), (19,3), (17,4)
	for (int y = 0; y < newBoard.height+2; y++) {
		for (int x = 0; x < newBoard.width+2; x++) {
			newBoard.filledBoard[(y * numCols) * x] = UNINIT;//-1 == uninitalized for count later
			newBoard.currentBoard[(y * numCols) * x] = UNINIT;
		}
	}
	/*
	Exception thrown: write access violation.
	newBoard.**filledBoard** was 0x223E18A.
	*/
	int row=0;
	int column=0;
	while (newBoard.currentMines < newBoard.numOfMines) {// -1 == mine on spot
		row = rand() % (newBoard.height+1)+1;
		column = rand() % (newBoard.width+1)+1;
		if (MINE != (newBoard.filledBoard[(row * numCols) * column])) {//if mine is already there skip and try again
			newBoard.filledBoard[(row * numCols) * column] = MINE;
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
	for (int y = 1; y < newBoard.width + 1; y++) {
		for (int x = 1; x < newBoard.height + 1; x++) {
			if (MINE != newBoard.filledBoard[(y * numCols) * x]) {
				newBoard.filledBoard[(y * numCols) * x] = 0;//redundant but good in case
			}
			if ((MINE == newBoard.filledBoard[((y - 1) * numCols) * x]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//up
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[((y - 1)* numCols) * (x - 1)]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//up and left		//access violation reading location due to left or up of first pos == nothing...
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[(y * numCols) * (x - 1)]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//left
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[((y + 1) * numCols) * (x - 1)]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//down and left
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[((y + 1) * numCols) * x]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//down
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[((y + 1) * numCols) * (x + 1)]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//down and right
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[(y * numCols) * (x + 1)]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//right
				newBoard.filledBoard[(y * numCols) * x]++;
			}
			if ((MINE == newBoard.filledBoard[((y - 1) * numCols) * (x + 1)]) && MINE != newBoard.filledBoard[(y * numCols) * x]) {//up and right
				newBoard.filledBoard[(y * numCols) * x]++;
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
	for (int i = 0; i < printBoard.width + 1; i++) {
		if (0 == i) {
			printf("[-]\t");
		}
		else {
			printf("[%d]\t", i);
		}
	}
	printf("\n\n");
	int numCols = printBoard.width;
	for (int y = 1; y < printBoard.height+1; y++) {
		printf("[%d]\t", y);
		for (int x = 1; x < printBoard.width+1; x++) {
			if (UNINIT == printBoard.currentBoard[(y * numCols) * x]) {
				printf("[?]\t");
			}
			//else if (0 == printBoard.currentBoard[x][y]) {
			//	printf("[0]\t");//just in case 0 is weird
			//}
			else{
				printf("[%d]\t", printBoard.currentBoard[(y * numCols) * x]);
			}

		}
		printf("\n\n");
	}
	printf("\n\n");
}
void printFinalBoard(MBoard printBoard) {
	for (int i = 0; i < printBoard.width+1; i++) {
		if (0 == i) {
			printf("[-]\t");
		}
		else {
			printf("[%d]\t", i);
		}
	}
	printf("\n\n");
	int numCols = printBoard.width;
	for (int y = 1; y < printBoard.height+1; y++) {
		printf("[%d]\t", y);
		for (int x = 1; x < printBoard.width+1; x++) {
			if (MINE == printBoard.filledBoard[(y * numCols) * x]) {
				printf("[M]\t");
			}
			else if (UNINIT == printBoard.filledBoard[(y * numCols) * x]) {
				printf("[?]\t");
			}
			//else if (0 == printBoard.currentBoard[x][y]) {
			//	printf("[0]\t");//just in case 0 is weird
			//}
			else {
				printf("[%d]\t", printBoard.filledBoard[(y * numCols) * x]);
			}

		}
		printf("\n\n");
	}
	printf("\n\n");
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
void deleteMBoard(MBoard* inputBoard) {
	int numCols = inputBoard->width + 2;
	for (int y = 0; y < inputBoard->height+2; y++) {
		for (int x = 0; x < inputBoard->width+2; x++) {
			inputBoard->filledBoard[(y * numCols) * x] = (int)NULL;
			inputBoard->currentBoard[(y * numCols) * x] = (int)NULL;
		}
	}
	free(inputBoard->currentBoard);
	free(inputBoard->filledBoard);

}