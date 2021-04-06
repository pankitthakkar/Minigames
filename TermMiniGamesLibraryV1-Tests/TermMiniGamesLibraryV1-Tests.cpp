#include "pch.h"
#include "CppUnitTest.h"
extern "C" {	//Put header files here with your name commented beside them for ownership!
	#include "Main.h" // Pankit	//leave commented until test is linked properly and headers can actually be added
	#include "Minesweeper.h" // Anthony
	#include "RPS.h" // Zahra
	#include "HangMan.h" // Mo
}
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TermMiniGamesLibraryV1Tests
{
	TEST_CLASS(Main)
	{
	public:
		
		TEST_METHOD(T0_01_)
		{
		}

		TEST_METHOD(T0_02_)
		{
		}

		TEST_METHOD(T0_03_)
		{
		}
	};

	TEST_CLASS(RPS)
	{
	public:

		TEST_METHOD(T01_01_)
		{
		}

		TEST_METHOD(T01_02_)
		{
		}

		TEST_METHOD(T01_03_)
		{
		}
	};

	TEST_CLASS(Minesweeper)
	{
	public:

		TEST_METHOD(T02_00_UpdateBoard_Succeed)
		{
			MBoard testBoard = initalizeBoard(25, 25, 10);
			testBoard.filledBoard[13][13] = 3;//sets to a "good" value so check works
			int check = updateBoardStub(&testBoard, 13, 13);
			deleteMBoard(&testBoard);
			Assert::AreEqual(check, 0);
		}

		TEST_METHOD(T02_01_UpdateBoard_Mine)
		{
			MBoard testBoard = initalizeBoard(25, 25, 10);
			testBoard.filledBoard[20][19] = MINE;
			int check = updateBoardStub(&testBoard, 20, 19);
			deleteMBoard(&testBoard);
			Assert::AreEqual(check, 1);
		}

		TEST_METHOD(T02_02_UpdateBoard_SameSpot)
		{
			MBoard testBoard = initalizeBoard(25, 25, 10);
			testBoard.currentBoard[10][10] = 3;
			int check = updateBoardStub(&testBoard, 10, 10);
			deleteMBoard(&testBoard);
			Assert::AreEqual(check, 2);
		}

		TEST_METHOD(T02_03_UpdateBoard_Off_Board)
		{
			MBoard testBoard = initalizeBoard(25, 25, 10);
			int check = updateBoardStub(&testBoard, 30, 30);
			Assert::AreEqual(check, 3);
		}
	};

	TEST_CLASS(Hangman)
	{
	public:

		TEST_METHOD(T03_01_)
		{
		}

		TEST_METHOD(T03_02_)
		{
		}

		TEST_METHOD(T03_03_)
		{
		}
	};
}