/*
 * unittest2.c
 * To test the function for the Minion Card, baronEffect.
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

#define increaseCoins 2
#define cardDiscard 1
#define newHandSize 4
#define gainAction 1

void newAssertEqualInt(int testVar, int expectedVar, char *testDefine)
{
	if(testVar == expectedVar)
	{
		printf("INFO: Test Success for %s.\n", testDefine);
	}
	else
	{
		printf("ERROR: Test FAILURE for %s.\n", testDefine);
	}
}

int main() {
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int maxHandCount = 5;
	
	printf ("TESTING baron card to see if only 1 estate is removed from the supply\n");
	int minions[maxHandCount];
	for (i = 0; i <  maxHandCount; i++)
    {
		minions[i] = minion;
	}
	
	struct gameState game, testGame;
	
	int k[10] = {baron, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	for(i = 0; i < numPlayers; i++)
	{
		game.handCount[i] = maxHandCount;
	}
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], minions, sizeof(int) * maxHandCount);
	
	memcpy(&testGame, &game, sizeof(struct gameState));

	
	printf("Testing Card is %s\n", TESTCARD);
	
	printf("TEST 1: Gain 2 coins\n");
	
	minionEffect(1, &testGame, currentPlayer, 0);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins + increaseCoins);
	printf("coin count = %d, expected = %d\n", testGame.numActions, game.numActions + gainAction);

	newAssertEqualInt(testGame.coins, game.coins + increaseCoins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "Hand Size");
	newAssertEqualInt(testGame.numActions, game.numActions + gainAction, "Action count");
	
}