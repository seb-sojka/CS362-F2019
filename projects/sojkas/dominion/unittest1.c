/*
 * unittest1.c
 * To test the function for the Baron Card, baronEffect.
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

const increaseCoins 4
const cardDiscardEstate 2
const cardDiscard 1

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
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int choiceDiscard = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int maxHandCount = 5;
	
	printf ("TESTING baron card to see if only 1 estate is removed from the supply\n");
	int estates[maxHandCount];
	int barons[maxHandCount];
	for (i = 0; i <  maxHandCount - 1; i++)
    {
		barons[i] = baron;
        estates[i] = estate;
	}
	
	estates[maxHandCount - 1] = baron;
	barons[maxHandCount - 1] = baron;
	struct gameState game, testGame;
	
	int k[10] = {baron, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	
	game.handCount[currentPlayer] = maxHandCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], estates, sizeof(int) * maxHandCount);
	
	printf("Testing Card is %s\n", TESTCARD);
	
	printf("TEST 1: Discard an estate\n");
	memcpy(&testGame, &game, sizeof(struct gameState));

	testGame.handCount[currentPlayer] = maxHandCount;
	//Set entire hand to estate expect baron card to play
	memcpy(testGame.hand[currentPlayer], estates, sizeof(int) * maxHandCount);
	baronEffect(1, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscardEstate);
	printf("coin count = %d, expected = %d\n", testGame->coins, game->coins + increaseCoins);

	newAssertEqualInt(testGame->coins, game->coins + increaseCoins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscardEstate, "Hand Size");
	
	printf("TEST 2: Gain an estate\n");
	game.handCount[currentPlayer] = maxHandCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], estates, sizeof(int) * maxHandCount);
	memcpy(&testGame, &game, sizeof(struct gameState));

	baronEffect(0, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame->coins, game->coins);
	
	if (testGame->discard[player][ testGame->discardCount[player] - 1] == estate)
	{
		printf("Last card in discard is not estate");
	}
	else
	{
		printf("Last card in discard is estate");
	}
	printf("Last card in discard is expected to be estate\n");
	newAssertEqualInt(testGame->coins, game->coins + increaseCoins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscardEstate, "hand size");
	newAssertEqualInt(testGame->discard[player][ testGame->discardCount[player] - 1], estate, "Estate was gained");
	
	printf("TEST 3: Try to discard an estate without 1\n");
	memcpy(&testGame, &game, sizeof(struct gameState));

	testGame.handCount[currentPlayer] = maxHandCount;
	//Set entire hand to estate expect baron card to play
	memcpy(testGame.hand[currentPlayer], barons, sizeof(int) * maxHandCount);
	baronEffect(1, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame->coins, game->coins);
	
	if (testGame->discard[player][ testGame->discardCount[player] - 1] == estate)
	{
		printf("Last card in discard is not estate");
	}
	else
	{
		printf("Last card in discard is estate");
	}
		printf("Last card in discard is expected to be estate\n");
	newAssertEqualInt(testGame->coins, game->coins + increaseCoins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscardEstate, "hand size");
	newAssertEqualInt(testGame->discard[player][ testGame->discardCount[player] - 1], estate, "Estate was gained");
}