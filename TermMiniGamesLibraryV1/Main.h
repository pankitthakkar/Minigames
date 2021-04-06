#pragma once
//All main menu and integration functions will be tested through this header, unless menu is given itsown .c/.h files
typedef struct User
{
    char username[10];
    char password;
    int minesweeper_highscore;
    int hangman_highscore;
    int RPS_highscore;

}USER;