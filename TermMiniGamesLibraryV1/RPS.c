#include "RPS.h"
bool startRPSGame()
{
	bool keepPlaying = true;
	srand(time(0));

	//Get User Input
	char input1[100];
	printf("\nPlease enter your choice of word 'Rock', 'Paper', or 'Scissor\n");
	printf("Press '2' to Exit the Game\n");
	printf("Choice: ");
	strcpy(input1, getStringInput()); //get user input
	if (strcmp(input1, "2") == 0)
	{
		//exit the game
		keepPlaying = false;
	} 
	else
	{

		//Get Computer Input
		char input2[100];
		getRandomComputerInput(&input2);

		//Start Game
		game(input1, input2);
	}


	return keepPlaying;

}


void game(char* playerOne, char* playerTwo)
{
	static char output[30];
	if ((strcmp(playerOne, rock) == 0) && (strcmp(playerTwo, paper) == 0))
	{
		displayResult(playerTwo, userLost);
	}
	else if ((strcmp(playerOne, rock) == 0) && (strcmp(playerTwo, scissor) == 0))
	{
		displayResult(playerTwo, userWon);
	}
	else if ((strcmp(playerOne, paper) == 0) && (strcmp(playerTwo, rock) == 0))
	{
		displayResult(playerTwo, userWon);
	}
	else if ((strcmp(playerOne, paper) == 0) && (strcmp(playerTwo, scissor) == 0))
	{
		displayResult(playerTwo, userLost);
	}
	else if ((strcmp(playerOne, scissor) == 0) && (strcmp(playerTwo, rock) == 0))
	{
		displayResult(playerTwo, userLost);
	}
	else if ((strcmp(playerOne, scissor) == 0) && (strcmp(playerTwo, paper) == 0))
	{
		displayResult(playerTwo, userWon);
	}
	else if ((strcmp(playerOne, rock) == 0) && (strcmp(playerTwo, rock) == 0))
	{
		displayResult(playerTwo, draw);
	}
	else if ((strcmp(playerOne, paper) == 0) && (strcmp(playerTwo, paper) == 0))
	{
		displayResult(playerTwo, draw);
	}
	else if ((strcmp(playerOne, scissor) == 0) && (strcmp(playerTwo, scissor) == 0))
	{
		displayResult(playerTwo, draw);
	}
}

void displayResult(char* computerChoice, char* result)
{
	printf("Result: %s\n", result);
	printf("Computer Choice: %s\n\n", computerChoice);

}

int getRandomNumber(int lower, int higher)
{
	//https://www.geeksforgeeks.org/generating-random-number-range-c/
	int num = (rand() % (higher - lower + 1)) + lower;
	return num;
}

void getRandomComputerInput(char* computerInput)
{
	int choice = getRandomNumber(1, 3);
	//char* computerInput = "";
	if (choice == 1)
	{
		strcpy_s(computerInput, 20, rock);
	}
	else if (choice == 2)
	{
		strcpy_s(computerInput, 20, paper);
	}
	else if (choice == 3)
	{
		strcpy_s(computerInput, 20, scissor);
	}
}
/*This function will get a string from the user*/
char* getStringInput()
{
	char userInput[WORD_SIZE] = { NULL };

	fgets(userInput, WORD_SIZE, stdin); //get input

	clearCRLF(userInput); 	//clear the return character from the userInput

	int stringLength = strlen(userInput) + 1;
	char* name = (char*)malloc(stringLength); //allocate memory for the char* according to the user string input
	strcpy(name, userInput);


	return name; //return the user input
}

/*
This function will search through the string and clean the '\n', it will end the string with '/0'
character.*/
void clearCRLF(char* str)
{
	char* whereIsCRLF = strchr(str, '\n');
	if (whereIsCRLF != NULL)
	{
		*whereIsCRLF = '\0';
	}
}