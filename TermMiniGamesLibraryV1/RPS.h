#pragma once
#pragma once
#pragma warning(disable: 4996)

//Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Constants
#define rock "Rock"
#define paper "Paper"
#define scissor "Scissor"
#define userLost "You Lost"
#define userWon "You Won"
#define draw "It is a Draw!"
#define WORD_SIZE 20

//Function Prototypes
bool startGame();
void game(char* playerOne, char* playerTwo);
void getRandomComputerInput(char* computerInput);
void displayResult(char* computerChoice, char* result);
int getRandomNumber(int lower, int higher);
char* getStringInput();
void clearCRLF(char* str);