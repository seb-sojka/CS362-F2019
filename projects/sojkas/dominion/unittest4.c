  
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


	int val = isGameOver(state);

	//return 0
	if (expectedVal == 0) {

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
		printf("TEST: isGameOver returns 0.\n");

		}

		if (expectedVal == 1) {
			printf("CASE: Less then 3 supply piles equal 0 \n");
			assertTrue(expectedVal, val);
			printf("TEST: isGameOver returns 1.\n");

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

		if (expectedVal == 0)
		{
			int choice = rand() % 4;
			int supplyPile = rand() % 25;
			if (choice == 0)
			{
				G.supplyCount[supplyPile] == 0;
				G.supplyCount[sea_hag] == 0;
				G.supplyCount[treasure_map] == 0;
			}
			else if (choice == 1)
			{
				G.supplyCount[supplyPile] == 0;
				supplyPile = rand() % 25;
				G.supplyCount[supplyPile] == 0;
				G.supplyCount[sea_hag] == 0;
			}
			else if (choice == 2)
			{
				G.supplyCount[supplyPile] == 0;
				supplyPile = rand() % 25;
				G.supplyCount[supplyPile] == 0;
				G.supplyCount[treasure_map] == 0;
			}
			else
			{
				G.supplyCount[supplyPile] == 0;
				supplyPile = rand() % 25;
				G.supplyCount[supplyPile] == 0;
				supplyPile = rand() % 25;
				G.supplyCount[supplyPile] == 0;
			}
			
		}

		testIsGameOver(expectedVal, &G);
	}

	return 0;

}