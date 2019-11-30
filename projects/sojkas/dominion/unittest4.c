  
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

/* HELPER FUNCTIONS FOR testBaron */

//go through the discard to check number of estates
int numDiscardEstates(struct gameState *state, int currentPlayer) {

	int discardEstates = 0;
	for (int i = 0; i < state->discardCount[currentPlayer]; i++) {
		if (state->discard[currentPlayer][i] == estate) {
			discardEstates++;
		}
	}
	return discardEstates;
}

//go through the hand to check number of estatess
int getNumEstates(struct gameState *state, int currentPlayer) {

	int numEstates = 0;
	for (int i = 0; i < numHandCards(state); i++) {
		if (state->hand[currentPlayer][i] == estate) {
			numEstates++;
		}
	}
	return numEstates;
}

int testBaron(int choice1, struct gameState *state, int currentPlayer) {

	int numEstates = getNumEstates(state, currentPlayer);
	int discardEstates = numDiscardEstates(state, currentPlayer);
	int supplyEstates = supplyCount(1, state);
	int money = state->coins;

	int val = baronEffect(choice1, state, currentPlayer);

	//Discard estate
	if (choice1 == 1 && numEstates > 0) {
		printf("CASE: Discard Estate\n");
		
		assertTrue(numEstates - 1, getNumEstates(state, currentPlayer));
		printf("TEST: -1 estate from hand.\n");
		
		assertTrue(money + 4, state->coins);
		printf("TEST: Coins + 4.\n");
		
		assertTrue(discardEstates + 1, numDiscardEstates(state, currentPlayer));
		printf("TEST: +1 estate to discard pile.\n");
	}

	//Gain estate
	else {
		printf("CASE: Gaining Estate\n");
		
		assertTrue(numEstates, getNumEstates(state, currentPlayer));
		printf("TEST: 1 more estate in hand.\n");
		
		assertTrue(money, state->coins);
		printf("TEST: Coins unchanged.\n");
		
		assertTrue(supplyEstates - 1, supplyCount(1, state));
		printf("TEST: 1 fewer estate in supply pile.\n");
	}

	return val;
}

int main (int argc, char** argv)	
{
    struct gameState G, tmp;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	printf("Tests for BARON\n");

	//Random test of basic card functionality	
	for (int i = 0; i < 30; i++) {
		int seed = rand() % 1000;
		int choice = rand() % 2;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		memcpy(&tmp, &G, sizeof(struct gameState));
		testBaron(choice, &G, 0);
		assertTrue(tmp.handCount[1], G.handCount[1]);
		printf("Test: Other players hand count did not change.");
	}

	//hard coded tests
	for(int i = 0; i < 10; i++){
		int seed = rand() % 1000;
		int choice = rand() % 2;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		for(int j = 0; j < supplyCount(estate, &G) * 8; j++){
			gainCard(1, &G, 0, 0);
		}

		testBaron(choice, &G, 0);
	}

	return 0;

}