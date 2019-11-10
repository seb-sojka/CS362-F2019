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
#include <time.h>

#define TESTCARD "baron"

#define increaseCoins 4
#define cardDiscardEstate 2
#define cardDiscard 1

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
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int handCount = rand() % MAX_HAND;
	
	printf ("TESTING baron card to see if only 1 estate is removed from the supply\n");
	int estates[handCount];
	int barons[handCount];
	for (i = 0; i <  handCount - 1; i++)
    {
		barons[i] = baron;
        estates[i] = estate;
	}
	
	estates[handCount - 1] = baron;
	barons[handCount - 1] = baron;
	struct gameState game, testGame;
	
	int k[10] = {baron, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	
	game.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], estates, sizeof(int) * handCount);
	
	printf("Testing Card is %s\n", TESTCARD);
	
	printf("TEST 1: Discard an estate\n");
	memcpy(&testGame, &game, sizeof(struct gameState));

	testGame.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(testGame.hand[currentPlayer], estates, sizeof(int) * handCount);
	baronEffect(1, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscardEstate);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins + increaseCoins);
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != estate)
	{
		printf("The estate was not discarded\n");
	}
	else
	{
		printf("The estate was discarded\n");
	}
	printf("Estate is expected to be discarded");
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != baron)
	{
		printf("The baron is not in discard\n");
	}
	else
	{
		printf("The baron is not in discard\n");
	}
	printf("Baron is expected to be discarded");
	newAssertEqualInt(testGame.coins, game.coins + increaseCoins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscardEstate, "Hand Size");
	printf("estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate]);

	newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate], "Estate removed from supply");
	printf("TEST 2: Gain an estate\n");
	game.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], estates, sizeof(int) * handCount);
	memcpy(&testGame, &game, sizeof(struct gameState));

	baronEffect(0, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != estate)
	{
		printf("The estate was not discarded\n");
	}
	else
	{
		printf("The estate was discarded\n");
	}
	printf("Estate is expected to be discarded");
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != baron)
	{
		printf("The baron is not in discard\n");
	}
	else
	{
		printf("The baron is not in discard\n");
	}
	printf("Baron is expected to be discarded");
	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "hand size");
	printf("estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate] - 1);

	newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate] - 1, "Estate removed from supply");
	
	printf("TEST 3: Try to discard an estate without 1\n");
	memcpy(&testGame, &game, sizeof(struct gameState));

	testGame.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(testGame.hand[currentPlayer], barons, sizeof(int) * handCount);
	baronEffect(1, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != estate)
	{
		printf("The estate was not discarded\n");
	}
	else
	{
		printf("The estate was discarded\n");
	}
	printf("Estate is expected to be discarded");
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != baron)
	{
		printf("The baron is not in discard\n");
	}
	else
	{
		printf("The baron is not in discard\n");
	}
	printf("Baron is expected to be discarded");
	printf("Estate Supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate] - 1);
	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "hand size");

	newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate] - 1, "Estate removed from supply");
	
	printf("TEST 4: Try to gain a estate with no supply of estate\n");
	game.supplyCount[estate] = 0;
	game.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], estates, sizeof(int) * handCount);
	memcpy(&testGame, &game, sizeof(struct gameState));

	baronEffect(0, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != estate)
	{
		printf("The estate was not discarded\n");
	}
	else
	{
		printf("The estate was discarded\n");
	}
	printf("Estate is not expected in discarded");
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != baron)
	{
		printf("The baron is not in discard\n");
	}
	else
	{
		printf("The baron is not in discard\n");
	}
	printf("Baron is expected to be discarded");
	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "hand size");
	printf("estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate]);

	newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate] , "Estate removed from supply");	
	printf("TEST 4: Try to gain a estate with no supply of estate\n");
	game.supplyCount[estate] = 0;
	game.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], barons, sizeof(int) * handCount);
	memcpy(&testGame, &game, sizeof(struct gameState));

	baronEffect(1, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != estate)
	{
		printf("The estate was not discarded\n");
	}
	else
	{
		printf("The estate was discarded\n");
	}
	printf("Estate is expected to be discarded");
	if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] != baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] != baron)
	{
		printf("The baron is not in discard\n");
	}
	else
	{
		printf("The baron is not in discard\n");
	}
	printf("Baron is expected to be discarded");
	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "hand size");
	printf("estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate] );

	newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate], "Estate removed from supply");	
	printf("TEST 5: Check to see if game ends after getting the last estate and 2 other supplies are empty\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.supplyCount[estate] = 1;
	game.supplyCount[k[0]] = 0;
	game.supplyCount[k[1]] = 0;
	game.handCount[currentPlayer] = handCount;
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], barons, sizeof(int) * handCount);
	memcpy(&testGame, &game, sizeof(struct gameState));

	baronEffect(1, &testGame, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	printf("coin count = %d, expected = %d\n", testGame.coins, game.coins);
	
	newAssertEqualInt(testGame.coins, game.coins, "coin count");
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard, "hand size");
	printf("estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate] - 1);

	newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate] - 1, "Estate removed from supply");
	newAssertEqualInt(testGame.supplyCount[estate], 0, "Estate supply count = 0");
}