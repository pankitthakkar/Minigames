#define _CRT_SECURE_NO_WARNINGS

#define LOOPING 1
#define MAX_LENGTH 30


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables

char Word[MAX_LENGTH];            // Word that has to be guessed 
char LetterGuessed[MAX_LENGTH];   // the amount of letters guessed correctly
char GuessedWord[] = "";          // the word the user is gonna guess
char Dashes[1] = "-";             // dashes representing the letters of the word

int incorrectGuesses = 6;         // represets the incorrect guesses with a max of 6

int getGuess(int wordLength);
void printDash(int wordLength);

// Main
int startHangmanGame(void)
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
                int result = getGuess(word_len);
                printDash(word_len);

                if (result > 0)
                    printf("incorrect attempts: %i of 6\n", incorrectGuesses);
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

int getGuess(int wordLength)
{
    int letters;
    int Correctletter = 0;

    printf("\nEnter a letter: \n");
    scanf(" %c", GuessedWord);

    int guessLen = strlen(LetterGuessed);
    if (Word[guessLen] == GuessedWord[0]) {
        LetterGuessed[guessLen] = GuessedWord[0];
        Correctletter++;
    }

    if (Correctletter > 0)
    {
        return 0;
    }
    else
    {
        incorrectGuesses++;
    }
    return incorrectGuesses;
}

void printDash(int wordLength)
{
    int letters;
    int i;                          // loop "counter" for function

    int guessLen = strlen(LetterGuessed);
    for (letters = 0; letters < wordLength; letters++)
    {
        if (letters < guessLen)
            printf("%c", LetterGuessed[letters]);
        else
            printf("%s", Dashes);
    }
    printf("\n");
}