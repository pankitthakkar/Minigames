//source for minesweeper game
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Main.h"
#include "Minesweeper.h"

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
	printCurrentBoard(gameBoard);
	printFinalBoard(gameBoard);
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
	newBoard.columns = xWidth;
	newBoard.rows = yHeight;
	//row = y
	//col = x
	//to find things in array = [(y * numCols) * x]
	int numRows = newBoard.rows+2;//+2 is for buffer around field
	int numCols = newBoard.columns+2;
	newBoard.currentBoard = (int**)malloc(numRows * sizeof(int*));
	//Check malloc
	if (newBoard.currentBoard == NULL)
	{
		fprintf(stderr,"\nERROR: User Board allocation\n");
	}
	//Allocate columns
	for (int i = 0; i < numRows; i++)
	{
		newBoard.currentBoard[i] = (int*)malloc(numCols * sizeof(int));
		//Check for malloc
		if (newBoard.currentBoard[i] == NULL)
		{
			deleteMBoard(&newBoard);
			exit(1);
		}
	}

	newBoard.filledBoard = (int**)malloc(numRows * sizeof(int*));
	//Check malloc
	if (newBoard.filledBoard == NULL)
	{
		fprintf(stderr, "\nERROR: User Board allocation\n");
	}
	//Allocate columns
	for (int i = 0; i < numRows; i++)
	{
		newBoard.filledBoard[i] = (int*)malloc(numCols * sizeof(int));
		//Check for malloc
		if (newBoard.filledBoard[i] == NULL)
		{
			deleteMBoard(&newBoard);
			exit(1);
		}
	}

	//error at (24,2), (19,3), (17,4)
	for (int row = 0; row < newBoard.rows+2; row++) {
		for (int column = 0; column < newBoard.columns+2; column++) {
			newBoard.filledBoard[row][column] = UNINIT;//-1 == uninitalized for count later
			newBoard.currentBoard[row][column] = UNINIT;
		}
	}
	/*
	Exception thrown: write access violation.
	newBoard.**filledBoard** was 0x223E18A.
	*/
	int row=0;
	int column=0;
	while (newBoard.currentMines < newBoard.numOfMines) {// -1 == mine on spot
		row = rand() % (newBoard.rows+1)+1;
		column = rand() % (newBoard.columns+1)+1;
		if (MINE != (newBoard.filledBoard[row][column])) {//if mine is already there skip and try again
			newBoard.filledBoard[row][column] = MINE;
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
	for (int row = 1; row < newBoard.rows + 1; row++) {
		for (int column = 1; column < newBoard.columns + 1; column++) {
			if (MINE != newBoard.filledBoard[row][column]) {
				newBoard.filledBoard[row][column] = 0;//redundant but good in case
			}
			if ((MINE == newBoard.filledBoard[row - 1][column]) && MINE != newBoard.filledBoard[row][column]) {//up
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row - 1][column - 1]) && MINE != newBoard.filledBoard[row][column]) {//up and left		//access violation reading location due to left or up of first pos == nothing...
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row][column - 1]) && MINE != newBoard.filledBoard[row][column]) {//left
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row + 1][column-1]) && MINE != newBoard.filledBoard[row][column]) {//down and left
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row + 1][column]) && MINE != newBoard.filledBoard[row][column]) {//down
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row + 1][column + 1]) && MINE != newBoard.filledBoard[row][column]) {//down and right
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row][column + 1]) && MINE != newBoard.filledBoard[row][column]) {//right
				newBoard.filledBoard[row][column]++;
			}
			if ((MINE == newBoard.filledBoard[row - 1][column + 1]) && MINE != newBoard.filledBoard[row][column]) {//up and right
				newBoard.filledBoard[row][column]++;
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
	for (int i = 0; i < printBoard.columns + 1; i++) {
		if (0 == i) {
			printf("[-]\t");
		}
		else {
			printf("[%d]\t", i);
		}
	}
	printf("\n\n");
	for (int row = 1; row < printBoard.rows+1; row++) {
		printf("[%d]\t", row);
		for (int col = 1; col < printBoard.columns+1; col++) {
			if (UNINIT == printBoard.currentBoard[row][col]) {
				printf("[?]\t");
			}
			//else if (0 == printBoard.currentBoard[x][y]) {
			//	printf("[0]\t");//just in case 0 is weird
			//}
			else{
				printf("[%d]\t", printBoard.currentBoard[row][col]);
			}

		}
		printf("\n\n");
	}
	printf("\n\n");
}
void printFinalBoard(MBoard printBoard) {
	for (int i = 0; i < printBoard.columns + 1; i++) {
		if (0 == i) {
			printf("[-]\t");
		}
		else {
			printf("[%d]\t", i);
		}
	}
	printf("\n\n");
	for (int row = 1; row < printBoard.rows + 1; row++) {
		printf("[%d]\t", row);
		for (int col = 1; col < printBoard.columns + 1; col++) {
			if (MINE == printBoard.filledBoard[row][col]) {
				printf("[M]\t");
			}
			else if (UNINIT == printBoard.filledBoard[row][col]) {
				printf("[?]\t");
			}
			//else if (0 == printBoard.currentBoard[x][y]) {
			//	printf("[0]\t");//just in case 0 is weird
			//}
			else {
				printf("[%d]\t", printBoard.filledBoard[row][col]);
			}
		}
		printf("\n\n");
	}
	printf("\n\n");
}
bool updateBoard(MBoard* currentBoard) {//gets user choice, first goes to checkInput then updates and returns board
	int inputRow;
	int inputColumn;
	printf("\nPlease enter a coordinate (ROW, COLUMN)\n");
	printf("ROW #:");
	scanf_s("%d", &inputRow);
	int newline = getc(stdin);//trailing newline?

	printf("COLUMN #:");
	scanf_s("%d", &inputColumn);
	newline = getc(stdin);//trailing newline?
	int checkValue = checkInput(*currentBoard, inputRow, inputColumn);
	if (inputRow > currentBoard->rows || inputColumn > currentBoard->columns) {
		printf("oops, that coordinate is off the board!\n");
		
	}
	if (0 == checkValue) {
		currentBoard->currentBoard[inputRow][inputColumn] = currentBoard->filledBoard[inputRow][inputColumn];//updates user's board with correct value
	}
	else if (1 == checkValue) {
		printf("oops, you stepped on a mine!\n");
		return false;
	}
	else if (2 == checkValue) {
		printf("oops, you already chose that spot\n");
	}
	else {
		fprintf(stderr, "\nERROR: failed to update Board\n");
		exit(2);
	}
	return true;//return if correct or they choose the same spot twice (which wouldn't be a fail)
}
int updateBoardStub(MBoard* testBoard, int testRow, int testColumn) {//stub for update board
	//int inputRow;
	//int inputColumn;
	//printf("\nPlease enter a coordinate (ROW, COLUMN)\n");
	//printf("ROW #:");
	//scanf_s("%d", &inputRow);
	//int newline = getc(stdin);//trailing newline?

	//printf("COLUMN #:");
	//scanf_s("%d", &inputColumn);
	//newline = getc(stdin);//trailing newline?
	int checkValue = checkInput(*testBoard, testRow, testColumn);
	if (testRow > testBoard->rows || testColumn > testBoard->columns) {
		printf("oops, that coordinate is off the board!\n");
		return 3;
	}
	if (0 == checkValue) {
		testBoard->currentBoard[testRow][testColumn] = testBoard->filledBoard[testRow][testColumn];//updates user's board with correct value
		return 0;
	}
	else if (1 == checkValue) {
		printf("oops, you stepped on a mine!\n");
		return 1;
	}
	else if (2 == checkValue) {
		printf("oops, you already chose that spot\n");
		return 2;
	}
	else {
		return 4;
	}
}

int checkInput(MBoard currentBoard, int inputRow, int inputColumn) {//checks input compared to current board and returns new board
	if (MINE == currentBoard.filledBoard[inputRow][inputColumn]) {//picked a mine
		return 1;
	}
	else if (UNINIT != currentBoard.currentBoard[inputRow][inputColumn]) {//sopt already chosen
		return 2;
	}
	else {
		return 0;//good input
	}
}

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
	int numCols = inputBoard->columns + 2;
	for (int row = 0; row < inputBoard->rows + 2; row++) {
		for (int col = 0; col < inputBoard->columns + 2; col++) {
			inputBoard->filledBoard[row][col] = (int)NULL;//to avoid leaking memory before releasing
			inputBoard->currentBoard[row][col] = (int)NULL;
			free((inputBoard->filledBoard[row][col]));
			free((inputBoard->currentBoard[row][col]));

		}
	}
	free(inputBoard->currentBoard);
	free(inputBoard->filledBoard);

}