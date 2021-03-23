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

		TEST_METHOD(T02_01_Board_Initalization)//this test always return true.. will have to breakpoint through it to see :)
		{
			
			
			MBoard testBoard = initalizeBoard(9, 9, 10);
			printFinalBoard(testBoard);
		}

		TEST_METHOD(T02_02_)
		{
		}

		TEST_METHOD(T02_03_)
		{
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