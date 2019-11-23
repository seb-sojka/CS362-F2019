/*
 * unittest2.c
 * To test the function for the mine Card, mineEffect.
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


#define TESTCARD "Mine"

#define CARDDISCARD 2
#define MAXPLAYER 4
#define NUMTREASURES 3
#define GAINCARD 1

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
    int numPlayers = rand() % (MAXPLAYER-1) + 2;
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
		golds[i] = gold;
	}

	int treasures[] = { copper, silver, gold };
	
	struct gameState game, testGame;
	
	int k[10] = {baron, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	

	printf("Testing Card is %s\n", TESTCARD);
		
	printf("TEST 1: Discard card and gain a treasure\n");
	
	int randTreasure = rand() % NUMTREASURES;
	int gainTreasure = 0;
	int minePos = rand() % 3;
	if(randTreasure == 0)
	{
		memcpy(newHand, coppers, sizeof(int) * randHandSize);
		newHand[minePos] = mine;
		gainTreasure = silver;
		printf("Coppere to be trashed and silver to be gained.\n");
	}
	else if(randTreasure == 1)
	{
		memcpy(newHand, silvers, sizeof(int) * randHandSize);
		newHand[minePos] = mine;
		gainTreasure = gold;
		printf("Silver to be trashed and gold to be gained.\n");
	}
	else
	{
		memcpy(newHand, golds, sizeof(int) * randHandSize);
		newHand[minePos] = mine;
		gainTreasure = gold;
		printf("Gold to be trashed and gold to be gained.\n");
	}
	
	game.handCount[currentPlayer] = randHandSize;
	game.whoseTurn = currentPlayer;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	int randTrash = rand() % randHandSize;
	while(randTrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	printf("Trash Num Card: %d\n", testGame.hand[currentPlayer][randTrash]);
	int ret = mineEffect(&testGame, minePos, randTrash, gainTreasure);
	printf("function return = %d, expected = %d\n", ret, 0);

	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + GAINCARD);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD, "hand count");
	printf("discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + CARDDISCARD);
	newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + CARDDISCARD, "discard count");
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
	printf("played card number = %d, expected = %d\n", testGame.playedCards[testGame.playedCardCount - 1], mine);
	newAssertEqualInt(testGame.playedCards[testGame.playedCardCount - 1], mine, "card played number");
	
	
	printf("TEST 2: Try to gain a non-treasure\n");
	int cardGain = rand() % 27;
	while(cardGain >= copper && cardGain <= gold)
	{
		cardGain = rand() % 27;
	}
	
	printf("Card number %d to try and gain\n", cardGain);
	randTreasure = rand() % NUMTREASURES;
	minePos = rand() % randHandSize;
	if(randTreasure == 0)
	{
		memcpy(newHand, coppers, sizeof(int) * randHandSize);
		newHand[minePos] = mine;
		gainTreasure = silver;
		printf("Copper to be trashed\n");
	}
	else if(randTreasure == 1)
	{
		memcpy(newHand, silvers, sizeof(int) * randHandSize);
		newHand[minePos] = mine;
		gainTreasure = gold;
		printf("Silver to be trashed\n");
	}
	else
	{
		memcpy(newHand, golds, sizeof(int) * randHandSize);
		newHand[minePos] = mine;
		gainTreasure = gold;
		printf("Gold to be trashed.\n");
	}
	randTrash = rand() % randHandSize;
	while(randTrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	game.whoseTurn = currentPlayer;
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	ret = mineEffect(&testGame, minePos, randTrash, cardGain);

	printf("function return = %d, expected = %d\n", ret, -1);
	newAssertEqualInt(ret, -1, "function return");
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	printf("supply count of gain card = %d, expected = %d\n", testGame.supplyCount[cardGain], game.supplyCount[cardGain]);
	newAssertEqualInt(testGame.supplyCount[cardGain], game.supplyCount[cardGain], "supply count of gained card");
	printf("number of cards card played = %d, expected = %d\n", testGame.playedCardCount, 0);
	newAssertEqualInt(testGame.playedCardCount, 0, "number of cards card played");
	printf("discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer]);
	newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer], "discard count");
	
	printf("TEST 3: Try to trash a non-treasure\n");
	int cardTrash = rand() % 27;
	while(cardTrash >= copper && cardTrash <= gold)
	{
		cardTrash = rand() % 27;
	}
	
	printf("Card number %d to trash\n", cardTrash);
	minePos = rand() % randHandSize;
	memcpy(newHand, coppers, sizeof(int) * randHandSize);
	newHand[minePos] = mine;
	cardGain = rand() % 3 + 4;
	randTrash = rand() % randHandSize;
	while(randTrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	newHand[randTrash] = cardTrash;
	game.whoseTurn = currentPlayer;
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	ret = mineEffect(&testGame, minePos, randTrash, cardGain);
	
	printf("function return = %d, expected = %d\n", ret, -1);
	newAssertEqualInt(ret, -1, "function return");

	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	printf("supply count of gain card = %d, expected = %d\n", testGame.supplyCount[cardGain], game.supplyCount[cardGain]);
	newAssertEqualInt(testGame.supplyCount[cardGain], game.supplyCount[cardGain], "supply count of gained card");
	printf("number of cards card played = %d, expected = %d\n", testGame.playedCardCount, 0);
	newAssertEqualInt(testGame.playedCardCount, 0, "number of cards card played");
	printf("discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer]);
	newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer], "discard count");

	printf("TEST 4: Try to gain treasure greater than 3 of the trash card\n");
	
	printf("Card number %d to trash\n", cardTrash);
	minePos = rand() % randHandSize;
	memcpy(newHand, coppers, sizeof(int) * randHandSize);
	newHand[minePos] = mine;

	randTrash = rand() % randHandSize;
	while(randTrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	game.whoseTurn = currentPlayer;
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	gainTreasure = gold;
	ret = mineEffect(&testGame, minePos, randTrash, gainTreasure);
	
	printf("function return = %d, expected = %d\n", ret, 0);
	newAssertEqualInt(ret, -1, "function return");
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	printf("supply count of gain card = %d, expected = %d\n", testGame.supplyCount[gainTreasure], game.supplyCount[gainTreasure]);
	newAssertEqualInt(testGame.supplyCount[gainTreasure], game.supplyCount[gainTreasure], "supply count of gained card");
	printf("number of cards card played = %d, expected = %d\n", testGame.playedCardCount, 0);
	newAssertEqualInt(testGame.playedCardCount, 0, "number of cards card played");
	printf("discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer]);
	newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer], "discard count");

	printf("TEST 5: Try to gain treasure that is cost 4 more than the trash card\n");
	
	printf("Card number %d to trash\n", cardTrash);
	minePos = rand() % randHandSize;
	memcpy(newHand, silvers, sizeof(int) * randHandSize);
	newHand[minePos] = mine;

	randTrash = rand() % randHandSize;
	while(randTrash == minePos)
	{
		randTrash = rand() % randHandSize;
	}
	game.whoseTurn = currentPlayer;
	game.handCount[currentPlayer] = randHandSize;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	gainTreasure = testTres4;
	ret = mineEffect(&testGame, minePos, randTrash, gainTreasure);
	
	printf("function return = %d, expected = %d\n", ret, 0);
	newAssertEqualInt(ret, -1, "function return");
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	printf("supply count of gain card = %d, expected = %d\n", testGame.supplyCount[gainTreasure], game.supplyCount[gainTreasure]);
	newAssertEqualInt(testGame.supplyCount[gainTreasure], game.supplyCount[gainTreasure], "supply count of gained card");
	printf("number of cards card played = %d, expected = %d\n", testGame.playedCardCount, 0);
	newAssertEqualInt(testGame.playedCardCount, 0, "number of cards card played");
	printf("discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer]);
	newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer], "discard count");

}