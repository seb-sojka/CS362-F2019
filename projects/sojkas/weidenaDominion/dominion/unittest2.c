/*
 * unittest2.c
 * To test the function for the Minion Card, callMinion.
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
#include <time.h>
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
	srand(time(NULL));
    int i;
    int seed = rand();
    int numPlayers = rand()%(MAX_PLAYERS-1)+2;
    int currentPlayer = rand() % numPlayers;
	int maxHandCount = rand()%MAX_HAND;
	printf("Number of Players: %d\n", numPlayers);
	int minions[maxHandCount];
	for (i = 0; i <  MAX_HAND; i++)
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
		game.handCount[i] = rand()%MAX_HAND;
	}
	game.whoseTurn = currentPlayer;
	memcpy(game.hand[currentPlayer], minions, sizeof(int) * maxHandCount);
	
	memcpy(&testGame, &game, sizeof(struct gameState));

	printf("Testing Card is %s\n", TESTCARD);
	
	printf("TEST 1: Gain 2 coins\n");
	
	callMinion(1, 0, &testGame, 0, currentPlayer);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins + increaseCoins);
	printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions + gainAction);
	
	for(i = 0; i < numPlayers; i++)
	{
		printf("hand count for player %d = %d, expected = %d\n", i, testGame.handCount[i], game.handCount[i]);
		newAssertEqualInt(testGame.handCount[i], game.handCount[i], "Hand Size");
	}
	newAssertEqualInt(testGame.coins, game.coins + increaseCoins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "Hand Size");
	newAssertEqualInt(testGame.numActions, game.numActions + gainAction, "Action count");
	
	printf("TEST 2: Discard hand and draw 4 cards for all players with 5 cards in hand\n");
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	memcpy(game.hand[currentPlayer], minions, sizeof(int) * 5);

	for(i = 0; i < numPlayers; i++)
	{
		game.handCount[i] = 5;
	}
	memcpy(&testGame, &game, sizeof(struct gameState));

	callMinion(0, 1, &testGame, 0, currentPlayer);
	
	for(i = 0; i < numPlayers; i++)
	{
		printf("hand count for player %d = %d, expected = %d\n", i, testGame.handCount[i], newHandSize);
		newAssertEqualInt(testGame.handCount[i], newHandSize, "Hand Size");
	}
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions + gainAction);

	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], newHandSize, "Current Player Hand Size");
	newAssertEqualInt(testGame.numActions, game.numActions + gainAction, "Action count");
	
	printf("TEST 3: Discard hand and draw 4 cards for all players with 5 or greater cards in hand\n");
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	for(i = 0; i < numPlayers; i++)
	{
		game.handCount[i] = rand()%(MAX_HAND-5)+5;
	}
	memcpy(game.hand[currentPlayer], minions, sizeof(int) * game.handCount[currentPlayer]);

	memcpy(&testGame, &game, sizeof(struct gameState));

	callMinion(0, 1, &testGame, 0, currentPlayer);
	
	for(i = 0; i < numPlayers; i++)
	{
		printf("hand count for player %d = %d, expected = %d\n", i, testGame.handCount[i], newHandSize);
		newAssertEqualInt(testGame.handCount[i], newHandSize, "Hand Size");
	}
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions + gainAction);

	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], newHandSize, "Current Player Hand Size");
	newAssertEqualInt(testGame.numActions, game.numActions + gainAction, "Action count");
	
	printf("TEST 4: Discard hand and draw 4 cards with other player have less than 5 cards\n");
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	for(i = 0; i < numPlayers; i++)
	{
		game.handCount[i] = rand()%5;
	}
	memcpy(game.hand[currentPlayer], minions, sizeof(int) * game.handCount[currentPlayer]);

	memcpy(&testGame, &game, sizeof(struct gameState));

	callMinion(0, 1, &testGame, 0, currentPlayer);
	
	for(i = 0; i < numPlayers; i++)
	{
		if(i != currentPlayer)
		{
			printf("hand count for player %d = %d, expected = %d\n", i, testGame.handCount[i], game.handCount[i]);
			newAssertEqualInt(testGame.handCount[i], game.handCount[i], "Hand Size");
		}
	}
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], newHandSize);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions + gainAction);

	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], newHandSize, "Current Player Hand Size");
	newAssertEqualInt(testGame.numActions, game.numActions + gainAction, "Action count");
	
	printf("TEST 5: Discard hand and draw 4 cards with other player have 4 cards\n");
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	for(i = 0; i < numPlayers; i++)
	{
		game.handCount[i] = 4;
	}
	memcpy(game.hand[currentPlayer], minions, sizeof(int) * game.handCount[currentPlayer]);

	memcpy(&testGame, &game, sizeof(struct gameState));

	callMinion(0, 1, &testGame, 0, currentPlayer);
	
	for(i = 0; i < numPlayers; i++)
	{
		if(i != currentPlayer)
		{
			printf("hand count for player %d = %d, expected = %d\n", i, testGame.handCount[i], game.handCount[i]);
			newAssertEqualInt(testGame.handCount[i], game.handCount[i], "Hand Size");
		}
	}
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], newHandSize);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions + gainAction);

	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], newHandSize, "Current Player Hand Size");
	newAssertEqualInt(testGame.numActions, game.numActions + gainAction, "Action count");
	
	
}