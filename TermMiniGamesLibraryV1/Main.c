//Team Based Software Programming Assignment.

//By: Al-Jaberi M, Amiri Z, Sasso A, Thakkar P
//Class: CSCN71930 - Winter 2020
//Created: March 04, 2021

//Revision History [PLEASE REMEMBER TO DO THIS WHEN YOU COMMIT STUFF AND ADD YOUR NAME!!!!]
	//March 4, 2021 - created and pushed shells for main and test projects, nothing more still need other to join GitHub -- Anthony
	//

//TODO for Integration / Main (Pankit): 
	//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Minesweeper.h"
#include "Main.h"

int main(void) {
	USER* testUser = (USER*) malloc(sizeof(USER));
	strcpy_s(testUser->username,(sizeof(char)*9),"testName");
	testUser->minesweeper_highscore = 10;
	RunMineSweeper(testUser);
	free(testUser);
	return 0;
}