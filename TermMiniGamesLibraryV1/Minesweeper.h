#pragma once
//Minesweeper header for tests / integration
void RunMineSweeper(USER* inputUser);//this will be called in main and pass the user into it to save scores

char** initalizeBoard(int XLength, int YLength);//initliaze board for new game

char** updateBoard(char** inputBoard, char xCoord, int yCoord);//gets user choice, first goes to checkInput then updates and returns board

bool checkInput(char** currentBoard, char xCoord, int yCoord);//checks input compared to current board and returns new board

int playerWin(USER* inputUser);//updates user if socre is higher then returns choice of 0 error, 1 continue, 2 exit

int playerLose();//returns choice of 0 error, 1 continue, 2 exit

int restartScreen();//restart screen seen after win or loss