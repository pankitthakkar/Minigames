//Team Based Software Programming Assignment.

//By: Al-Jaberi M, Amiri Z, Sasso A, Thakkar P
//Class: CSCN71930 - Winter 2020
//Created: March 04, 2021

//Revision History [PLEASE REMEMBER TO DO THIS WHEN YOU COMMIT STUFF AND ADD YOUR NAME!!!!]
	//March 4, 2021 - created and pushed shells for main and test projects, nothing more still need other to join GitHub -- Anthony
	//

//TODO for Integration / Main (Pankit): 
	//


#include <stdio.h>
#include "Main.h"
#include "HangMan.h"
#include "RPS.h"
#include "Minesweeper.h"

int main()
{
	int b;
	printf("Welcome");

	USER user;
	user.hangman_highscore = 0;
	user.minesweeper_highscore = 0;
	user.RPS_highscore = 0;

	printf("\n\n Input your name: ");
	scanf("%s", user.username);

	printf("\n\n 1. RPS\n 2. HangMan \n 3. MineSweeper\n 0. Exit\n\n");
	scanf("%d", &b);


	switch (b)
	{
	case 1:
		startRPSGame();
		break;

	case 2:
		startHangmanGame();
		break;

	case 3:
		RunMineSweeper(&user);
		break;

	default:
		break;
	}
}