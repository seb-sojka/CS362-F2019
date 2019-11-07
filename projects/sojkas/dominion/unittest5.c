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

#define TESTCARD "Mine"

#define CARDDISCARD 2
#define MAXPLAYER 4

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
    int numPlayers = rand() % MAXPLAYER;
    int currentPlayer = rand() % numPlayers;
	
	int randHandSize = rand() % (MAX_HAND - 2) + 2;
	int newHand[randHandSize];
	int golds[randHandSize];
	int silvers[randHandSize];
	int coppers[randHandSize];
	for (i = 0; i <  randHandSize; i++)
    {
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = golds;
	}

	int treasures[] = { copper, silver, gold };
	
	struct gameState game, testGame;
	
	int k[10] = {baron, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("Testing Card is %s\n", TESTCARD);
		
	printf("TEST 1: Discard card and gain a treasure\n");
	
	int randTreasure = rand() % treasures.length();
	int gainTreasure = 0;
	int minePos = rand() % randHandSize;
	if(randTreasure == 0)
	{
		newHand = coppers;
		newHand[minePos] = mine;
		gainTreasure = sliver;
		printf("Coppere to be trashed and silver to be gained.\n");
	}
	else if(randTreasure == 1)
	{
		newHand = silvers;
		newHand[minePos] = mine;
		gainTreasure = gold;
		printf("Silver to be trashed and gold to be gained.\n");
	}
	else
	{
		newHand = golds;
		newHand[minePos] = mine;
		gainTreasure = gold;
		printf("Gold to be trashed and gold to be gained.\n");
	}
	
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	int randTrash = rand() % randHandSize;
	while(randtrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	
	mineEffect(testGame, minePos, randTrash, gainTreasure);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - cardDiscard);
	if (testGame.discard[currentPlayer][ testGame.discardCount[currentPlayer] - 2] == gainTreasure)
	{
		printf("The correct treasure was gained\n");
	}
	else
	{
		printf("The correct treasure was not gained\n");
	}
	
	if (testGame.discard[currentPlayer][ testGame.discardCount[currentPlayer] - 1] == mine)
	{
		printf("The mine card was discard\n");
	}
	else
	{
		printf("The mine card was not the last card discarded\n");
	}
	
	printf("TEST 2: Try to gain a non-treasure\n");
	int cardGain = rand() % 27;
	while(cardGain >= copper && cardGain <= gold)
	{
		cardGain = rand() % 27;
	}
	
	printf("Card number %d to try and gain\n", cardGain);
	randTreasure = rand() % treasures.length();
	int minePos = rand() % randHandSize;
	if(randTreasure == 0)
	{
		newHand = coppers;
		newHand[minePos] = mine;
		printf("Copper to be trashed.\n");
	}
	else if(randTreasure == 1)
	{
		newHand = silvers;
		newHand[minePos] = mine;
		printf("Silver to be trashed.\n");
	}
	else
	{
		newHand = golds;
		newHand[minePos] = mine;
		printf("Gold to be trashed.\n");
	}
	int randTrash = rand() % randHandSize;
	while(randtrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	int ret = mineEffect(testGame, minePos, randTrash, cardGain);
	
	if(ret == -1)
	{
		printf("Mine return error. Return -1);
	}
	else
	{
		printf("Mine return success. Return 0);
	}
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	printf("supply count of gain card = %d, expected = %d\n", testGame.supplyCount[cardGain], game.supplyCount[cardGain]);
	newAssertEqualInt(testGame.supplyCount[cardGain], game.supplyCount[cardGain], "supply count of gained card");
	
	printf("TEST 3: Try to trash a non-treasure\n");
	int cardTrash = rand() % 27;
	while(cardTrash >= copper && cardTrash <= gold)
	{
		cardTrash = rand() % 27;
	}
	
	printf("Card number %d to trash\n", cardTrash);
	randTreasure = rand() % treasures.length();
	int minePos = rand() % randHandSize;
	if(randTreasure == 0)
	{
		newHand = coppers;
		newHand[minePos] = mine;
	}
	else if(randTreasure == 1)
	{
		newHand = silvers;
		newHand[minePos] = mine;
	}
	else
	{
		newHand = golds;
		newHand[minePos] = mine;
	}
	int randTrash = rand() % randHandSize;
	while(randtrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	newHand[randTrash] = cardTrash;
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	int ret = mineEffect(testGame, minePos, randTrash, cardGain);
	
	if(ret == -1)
	{
		printf("Mine return error. Return -1);
	}
	else
	{
		printf("Mine return success. Return 0);
	}
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	printf("supply count of gain card = %d, expected = %d\n", testGame.supplyCount[cardGain], game.supplyCount[cardGain]);
	newAssertEqualInt(testGame.supplyCount[cardGain], game.supplyCount[cardGain], "supply count of gained card");
}