  
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


void assertTrue(int test, int value) {
	if (test == value) {
		printf("PASSED\t");
	}
	else {
		printf("FAILED\t");
	}
}

int testIsGameOver(int expectedVal, struct gameState *state) {


	//return 0
	int val;
	if (expectedVal == 1) {

		int choice = rand() % 4;
		int supplyPile = rand() % 5;
		printf("Supply pile is: %d\n", supplyPile);
		if (choice == 0)
		{
			state->supplyCount[supplyPile] = 0;
			state->supplyCount[sea_hag] = 0;
			state->supplyCount[treasure_map] = 0;
		}
		else if (choice == 1)
		{
			state->supplyCount[supplyPile] = 0;
			supplyPile = (rand() % 5)+5;
			state->supplyCount[supplyPile] = 0;
			state->supplyCount[sea_hag] = 0;
		}
		else if (choice == 2)
		{
			state->supplyCount[supplyPile] = 0;
			supplyPile = (rand() % 5)+5;
			state->supplyCount[supplyPile] = 0;
			state->supplyCount[treasure_map] = 0;
		}
		else
		{
			state->supplyCount[supplyPile] = 0;
			supplyPile = (rand() % 5)+5;
			state->supplyCount[supplyPile] = 0;
			supplyPile = (rand() % 5)+10;
			printf("Supply pile is: %d\n", supplyPile);
			state->supplyCount[supplyPile] = 0;
		}
		
		val = isGameOver(state);

		if(state->supplyCount[sea_hag] == 0 && state->supplyCount[treasure_map] == 0)
		{
			printf("CASE: Three supply piles equal 0, one is sea_hag and one is treasure_map \n");
		}

		else if(state->supplyCount[sea_hag] == 0)
		{
			printf("CASE: Three supply piles equal 0, one is sea_hag \n");
		}

		else if (state->supplyCount[treasure_map] == 0){
			printf("CASE: Three supply piles equal 0, one is treasure_map \n");
		}

		else{
			printf("CASE: Three supply piles equal 0, neither is sea_hag nor treasure_map \n");
		}

		assertTrue(expectedVal, val);
		printf("TEST: isGameOver returns 1.\n");

	}

	else {
		val = isGameOver(state);
		printf("CASE: Less then 3 supply piles equal 0 \n");
		assertTrue(expectedVal, val);
		printf("TEST: isGameOver returns 0.\n");
	}



	return val;
}

int main (int argc, char** argv)	
{
    struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	printf("Tests for isGameOver\n");

	//hard coded tests
	for(int i = 0; i < 10; i++){
		int seed = rand() % 1000;
		int expectedVal = rand() % 2;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		for (int i=0; i<treasure_map+1; i++)
		{
			G.supplyCount[i] = 10;
		}

		testIsGameOver(expectedVal, &G);
	}

	return 0;

}