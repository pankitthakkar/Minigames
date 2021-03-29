#define _CRT_SECURE_NO_WARNINGS

#define LOOPING 1
#define MAX_LENGTH 30


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Header.h"


// Variables

char Word[MAX_LENGTH];            // Word that has to be guessed 
char LetterGuessed[MAX_LENGTH];   // the amount of letters guessed correctly
char GuessedWord[] = "";          // the word the user is gonna guess
char Dashes[1] = "-";             // dashes representing the letters of the word

int incorrectGuesses = 6;         // represets the incorrect guesses with a max of 6

// Main
int main(void)
{
    char answer;
    while (LOOPING)
    {
        printf("Please enter a word: ");
        scanf("%s", Word);

        int word_len = strlen(Word);
        memset(LetterGuessed, 0, sizeof LetterGuessed);

        incorrectGuesses = 0;

        while (incorrectGuesses < 6)
        {
            if (strlen(LetterGuessed) == word_len)
            {
                printDash(word_len);
                break;
            }
            else
            {
                printf("incorrect attempts: %i of 6\n", incorrectGuesses);
                printDash(word_len);
                getGuess(word_len);
            }
        }

        if (incorrectGuesses < 6)
        {
            puts("\n Congrats you guessed the word,You Won!\n");
            return 0;
        }
        else
        {
            puts("\n Hard luck, You Lost!\n");
            return 0;
        }
    }
    
}
// Functions

int Guess(int wordLength)
{
    int letters;
    int Correctletter = 0;

    printf("\nEnter a letter: \n");
    scanf(" %c", GuessedWord);

    for (letters = 0; letters < wordLength; letters++)
    {
        if (GuessedWord[0] == Word[letters])
        {
            LetterGuessed[letters] = GuessedWord[0];

            Correctletter++;
        }
    }
    if (Correctletter > 0)
    {
        return;
    }
    else
    {
        incorrectGuesses++;
    }
    return incorrectGuesses;
}

void Dash(int wordLength)
{
    int letters;
    int i;                          // loop "counter" for function

    for (letters = 0; letters < wordLength; letters++)
    {
        printf("%c", LetterGuessed[letters]);
        printf(" ");
    }
    printf("\n");

    for (i = 0; i < wordLength; i++)
    {
        printf("%s", Dashes);
        printf(" ");
    }
}