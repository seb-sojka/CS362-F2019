/*
 * unittest2.c
 * To test the function for the ambassador Card, ambassadorEffect.
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

#define TESTCARD "ambassador"

#define MAXPLAYER 4
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
	srand(time(NULL));

    int numPlayers = rand() % (MAXPLAYER - 1) + 2;
    int currentPlayer =  rand() % numPlayers ;
	int randHandSize = rand() % (MAX_HAND - 2) + 2;
	printf("Number Player: %d\n", numPlayers);
	int newHand[randHandSize];
		
	int k[10] = {baron, embargo, ambassador, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};
	int allCards[17];
	memcpy(allCards, k, sizeof k);
	
	//Add curse, treasures, and victory cards to posssible cards to return
	for(i = curse; i <= gold; i++)
	{
		allCards[10 + i] = i;
	}
		
	int cardTrash = allCards[rand()%17];
	struct gameState game, testGame;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);

	printf("Testing Card is %s\n", TESTCARD);
	
	printf("TEST 1: Return an acceptable amount of cards\n");
	game.handCount[currentPlayer] = randHandSize;
	game.whoseTurn = currentPlayer;
	for (i = 0; i <  randHandSize; i++)
	{
		newHand[i] = cardTrash;
	}
	int ambassPos = rand() % randHandSize;
	newHand[ambassPos] = ambassador;
	
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	
	int revealPos = ambassPos;
	while (revealPos == ambassPos)
	{
		revealPos = rand() % randHandSize;
	}
	int returnNum = rand()%3;
	
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	ambassadorEffect(revealPos, returnNum, &testGame, ambassPos, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - 1 - returnNum);
	printf("supply count = %d, expected = %d\n", testGame.supplyCount[cardTrash], game.supplyCount[cardTrash] + returnNum - (numPlayers - 1));
	
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - 1 - returnNum, "hand count");
	newAssertEqualInt(testGame.supplyCount[cardTrash], game.supplyCount[cardTrash] + returnNum - (numPlayers - 1), "supply count");
	
	for(i = 0; i < numPlayers; i++)
	{
		if( i != currentPlayer)
		{
			printf("card number of discard for player %d = %d, expected =%d\n", i, testGame.discard[i][ testGame.discardCount[i] - 1], cardTrash);
			newAssertEqualInt(testGame.discard[i][ testGame.discardCount[i] - 1], cardTrash, "players gaining correct card");
		}
	}
	
	printf("TEST 2: Trying to return over 2 cards\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	randHandSize = rand() % (MAX_HAND - 2) + 2;
	cardTrash = allCards[rand()%17];
	game.handCount[currentPlayer] = randHandSize;
	
	for (i = 0; i <  randHandSize; i++)
	{
		newHand[i] = cardTrash;
	}
	
	ambassPos = rand() % randHandSize;
	newHand[ambassPos] = ambassador;
	
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	
	revealPos = ambassPos;
	while (revealPos == ambassPos)
	{
		revealPos = rand() % randHandSize;
	}
	returnNum = rand() % (randHandSize - 3) + 3;
	
	memcpy(&testGame, &game, sizeof(struct gameState));
	int ret = ambassadorEffect(revealPos, returnNum, &testGame, ambassPos, currentPlayer);
	if(ret == -1)
	{
		printf("Ambassador return error. Return -1\n");
	}
	else
	{
		printf("Ambassador return success. Return 0\n");
	}
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	printf("supply count = %d, expected = %d\n", testGame.supplyCount[cardTrash], game.supplyCount[cardTrash]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	newAssertEqualInt(testGame.supplyCount[cardTrash], game.supplyCount[cardTrash], "supply count");
	
	printf("TEST 3: Trying to return over negative cards\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	randHandSize = rand() % (MAX_HAND - 2) + 2;
	cardTrash = allCards[rand()%17];
	game.handCount[currentPlayer] = randHandSize;
	
	for (i = 0; i <  randHandSize; i++)
	{
		newHand[i] = cardTrash;
	}
	
	ambassPos = rand() % randHandSize;
	newHand[ambassPos] = ambassador;
	
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	
	revealPos = ambassPos;
	while (revealPos == ambassPos)
	{
		revealPos = rand() % randHandSize;
	}
	returnNum = -1;
	
	memcpy(&testGame, &game, sizeof(struct gameState));
	ret = ambassadorEffect(revealPos, returnNum, &testGame, ambassPos, currentPlayer);
	if(ret == -1)
	{
		printf("Ambassador return error. Return -1\n");
	}
	else
	{
		printf("Ambassador return success. Return 0\n");
	}
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	printf("supply count = %d, expected = %d\n", testGame.supplyCount[cardTrash], game.supplyCount[cardTrash]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	newAssertEqualInt(testGame.supplyCount[cardTrash], game.supplyCount[cardTrash], "supply count");
	
	printf("TEST 4: Try to reveal the played card\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	randHandSize = rand() % (MAX_HAND - 2) + 2;
	cardTrash = allCards[rand()%17];
	game.handCount[currentPlayer] = randHandSize;
	
	for (i = 0; i <  randHandSize; i++)
	{
		newHand[i] = cardTrash;
	}
	
	ambassPos = rand() % randHandSize;
	newHand[ambassPos] = ambassador;
	
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	
	revealPos = ambassPos;
	returnNum = rand() % 3;
	
	memcpy(&testGame, &game, sizeof(struct gameState));
	ret = ambassadorEffect(revealPos, returnNum, &testGame, ambassPos, currentPlayer);
	if(ret == -1)
	{
		printf("Ambassador return error. Return -1\n");
	}
	else
	{
		printf("Ambassador return success. Return 0\n");
	}
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
	printf("supply count = %d, expected = %d\n", testGame.supplyCount[cardTrash], game.supplyCount[cardTrash]);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer], "hand count");
	newAssertEqualInt(testGame.supplyCount[cardTrash], game.supplyCount[cardTrash], "supply count");
	
	printf("TEST 5: Increase in supply count is correct\n");
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	int handSize = 50;
	game.handCount[currentPlayer] = handSize;
	cardTrash = allCards[rand()%17];
	for (i = 0; i <  handSize; i++)
	{
		newHand[i] = cardTrash;
	}
	
	ambassPos = rand() % handSize;
	newHand[ambassPos] = ambassador;
	
	//Set entire hand to estate expect baron card to play
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * handSize);
	
	revealPos = ambassPos;
	while (revealPos == ambassPos)
	{
		revealPos = rand() % handSize;
	}
	returnNum = rand() % 3;
	
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	ambassadorEffect(revealPos, returnNum, &testGame, ambassPos, currentPlayer);
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - 1 - returnNum);
	printf("supply count = %d, expected = %d\n", testGame.supplyCount[cardTrash], game.supplyCount[cardTrash] + returnNum - (numPlayers - 1));
	
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - 1 - returnNum, "hand count");
	newAssertEqualInt(testGame.supplyCount[cardTrash], game.supplyCount[cardTrash] + returnNum - numPlayers, "supply count");
	
	for(i = 0; i < numPlayers; i++)
	{
		if( i != currentPlayer)
		{
			printf("card number of discard for player %d = %d, expected =%d\n", i, testGame.discard[i][ testGame.discardCount[i] - 1], cardTrash);
			newAssertEqualInt(testGame.discard[i][ testGame.discardCount[i] - 1], cardTrash, "players gaining correct card");
		}
	}
}