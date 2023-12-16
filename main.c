#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"
#include <conio.h>

enum Status { CONTINUE, WON, LOST };
enum Status gameStatus;

//This function rolls 2 dices and returns the sum between the two
int roll2Dice(void); 

//This function rolls 1 dice and returns the throw
int roll1Dice(void); 

//The game Craps
void craps(void); 

//Helper function for the game abyss
int abyssRules(int plr1, int sumPrev, int plr2);

//The game abyss
void abyss(void); 

//Helper function for pigs
//This function takes in the sum of the player
//Makes a dice throw and calculates the sum accordingly
//Returns the dice throw as a int
int pigsThrow(int sum);

//The game pigs
void pigs(void); 

//Displays the main menu
void displayMainMenu(void);



int main(void)
{
	srand(time(NULL)); //New random seed
	int answer;

	while (true)
	{
		displayMainMenu();

		printf("Your choice? ");
		scanf("%d", &answer);

		switch (answer)
		{
		case 1:
			craps();
			break;
		case 2:
			abyss();
			break;
		case 3:
			pigs();
			break;
		case 0:
			exit(0);
		default: puts("Please enter a valid option"); break;
		}
	}
}

int roll2Dice(void) {
	int die1 = 1 + (rand() % 6);
	int die2 = 1 + (rand() % 6);
	printf("Player rolled %d + %d = %d\n", die1, die2, die1 + die2);
	Sleep(1000);
	return die1 + die2;
}

//Function to roll one dice
int roll1Dice() {

	int die1 = 1 + (rand() % 6);

	return die1;
}

void craps(void)
{
	int myPoint;
	int sum = roll2Dice();

	switch (sum) {
	case 7:
	case 11:
		gameStatus = WON;
		break;

	case 2:
	case 3:
	case 12:
		gameStatus = LOST;
		break;

	default:
		gameStatus = CONTINUE;
		myPoint = sum;
		printf("Point is %d\n", myPoint);
		break;
	}

	while (CONTINUE == gameStatus) {
		sum = roll2Dice();


		if (sum == myPoint) {
			gameStatus = WON;
		}
		else {
			if (7 == sum) {
				gameStatus = LOST;
			}
		}
	}
	if (WON == gameStatus) {
		puts("Congratulations you won!");
	}
	else {
		puts("Player loses im sori");
	}

}

//Sum for plr1, Prev sum for player1, Sum for pl2
int abyssRules(int plr1, int sumPrev, int plr2)
{

	//If player X gets to a number between 1 and 12, and the player Y is on exactly that number, player X is sent back down to 0.
	if (plr1 > 1 && plr1 < 12)
	{
		if (plr2 == plr1) {
			plr1 = 0;
			puts("Got between 1-12 and the previous player was sadly exactly on that number, Back to 0!");
		}

	}

	//If player Xgets to a number between 14 and 24, and the player Y is on exactly that number, player X is sent back down to 12.
	if (plr1 > 14 && plr1 < 24)
	{
		if (plr2 == plr1) {
			plr1 = 12;
			puts("Got between 14-24 and the previous player was sadly exactly on that number, Back to 12!");
		}

	}

	//If player gets to number 25 and the computer is on exactly that number, player is sent back down to 14.
	if (plr1 == 25 && plr2 == plr1)
	{

		puts("Got 25 and the previous player was sadly exactly on that number, Back to 14!");
		plr1 = 14;
	}


	if (plr1 > 26) {
		puts("Got over 26, Rolls back to previous sum");

		return sumPrev;
	}


	if (plr1 == 13) //ABYSS
	{
		puts("Got 13 and lost");
		gameStatus = LOST;

	}
	//A player has to roll exactly the number required to get 26 from her current sum.
	if (plr1 == 26) //WON
	{
		puts("Got exactly 26 and won");
		gameStatus = WON;

	}

	return plr1;
}

void abyss(void)
{
	int sumP = 0; //Sum for player
	int sumC = 0; //Sum for computer
	int sumPrevP = 0; //Previous sum for player used to calculate the previous throw
	int sumPrevC = 0; //Previous sum for computer used to calculate the previous throw

	gameStatus = CONTINUE;

	while (gameStatus == CONTINUE)
	{
		//Player turn to ROLL
		puts("Press any key to roll");
		(void)_getch(); //Used to wait for a key input to roll the dice
		sumPrevP = sumP; //Save previous sum
		sumP += roll1Dice(); //The new sum after rolling the dice
		printf("Player rolled %d\n", sumP - sumPrevP); //the throw
		printf("Players sum is now %d\n", sumP); //The total sum
		sumP = abyssRules(sumP, sumPrevP, sumC); //The rules of the game and returns the new sum


		puts("--------------------");

		//Computers turn to roll
		sumPrevC = sumC;
		sumC += roll1Dice();
		printf("Computer rolled %d\n", sumC - sumPrevC);
		printf("Computers sum is now %d\n", sumC);
		sumC = abyssRules(sumC, sumPrevC, sumP);

		puts("--------------------");

	}
}

int pigsThrow(int sum)
{
	int dice;
	dice = roll1Dice();
	printf(" %d ", dice);
	if (dice == 1) sum = 0; //Reset score
	else sum += dice;

	return sum;
}

void pigs(void) {
	int sumP = 0; //sum of player
	int sumC = 0; //sum of computer
	int dice; //The dice
	int hold = 0;

	gameStatus = CONTINUE;

	while (gameStatus == CONTINUE)
	{
		// PLAYERS TURN
		do {
			puts("Enter 1 to hold or 0 to roll");

			scanf("%d", &hold);
			if (hold) break;

			//** DICE THROW **//
			printf("The player rolled");
			sumP = pigsThrow(sumP);
			printf("\n");
			if (sumP == 0) break;
			//*****************
		
			//Break if player won
			if (sumP >= 100) {
				gameStatus = WON;
				puts("You win");
				return;
			}

			printf("Your total sum is %d\n", sumP);

		} while (1);

		puts("------------------------------------------");

		//COMPUTERS TURN
		do {

			
			//** DICE THROW 1 **//
			printf("The computer rolled ");
			sumC = pigsThrow(sumC);
			if (sumC == 0) break;
			//******************

			//** DICE THROW 2 **//
			printf(" & ");
			sumC = pigsThrow(sumC);
			if (sumC == 0) break;
			printf("\n");
			//******************

			if (sumC >= 100) {
				gameStatus = LOST;
				puts("You lose");
				return;
			}

			printf("Computer score is %d\n", sumC);

			//A randomized decision wether the computer is supposed to hold or not
			if ((rand() % 2) - 1)
			{
				puts("The computer choosed to hold");
				break;
			}

		} while (1);

		puts("\n------------------------------------------");


	}
}

void displayMainMenu(void)
{
	puts("Which game would you like to play ? ");
	puts("	Enter 1 for Craps");
	puts("	Enter 2 for The Abyss");
	puts("	Enter 3 for Pig");
	puts("	Enter 0 to Quit ");

}
