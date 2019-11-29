/*
 * unittest8.c
 * To test the function cardEffect and how bonus coins are treated from played cards 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest8: unittest8.c dominion.o rngs.o
 *      gcc -o unittest8 -g  unittest8.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "Ambassador"

#define TESTLIMIT 10000
#define ACTIONINCREASE 1
#define INCREASECOINS 2
//Discard count after baron when not discard estate
#define DISCARDNUM 1
#define NUMBERCARDS 2
#define DRAWCARDS 2

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

int valueInArray(int val, int array[])
{
	int i;
	for(i = 0; i < sizeof(array) / sizeof(array[0]); i++)
    {
        if(array[i] == val)
            return 1;
    }
	return 0;
}

void setUpRandomGame(struct gameState* game)
{
	int seed = rand();
	//Limit cards in play to the cards avialbe to choose from and do not duplicate them.
	int i = 0;
	int k[10] = {ambassador, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int allCards[17];
	memcpy(allCards, k, sizeof k);
	//Add curse, treasures, and victory cards to posssible cards to return
	for(i = curse; i <= gold; i++)
	{
		allCards[10 + i] = i;
	}
	//Limit number of players from 2 to 4 for testing as that is the limit of players
	int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
	int currentPlayer =  rand() % numPlayers;
	//Init Game
	initializeGame(numPlayers, k, seed, game);
	
	game->whoseTurn = currentPlayer;
}

int main() 
{
	printf("Testing Card is %s\n", TESTCARD);
	srand(time(NULL));
	struct gameState game, testGame;
	int handPos = 0;
	memset(&game, 0, sizeof(struct gameState));
	memset(&testGame, 0, sizeof(struct gameState));
	setUpRandomGame(&game);
	int currentPlayer = game.whoseTurn;
	int nextPlayer = game.whoseTurn + 1;
	if(nextPlayer >= game.numPlayers)
	{
		nextPlayer = 0;
	}

	printf("Test 1: Try to return 1 duchy to supply with only 1 in hands and a duchy card to return at card hand index 2\n");
	setUpRandomGame(&game);
	game.handCount[game.whoseTurn] = 3;
	game.hand[game.whoseTurn][0] = ambassador;
	game.hand[game.whoseTurn][1] = duchy;
	game.hand[game.whoseTurn][2] = estate;
	printf("dcuhy Number: %d\n", duchy);
	memcpy(&testGame, &game, sizeof(struct gameState));
	int returnVal = cardEffect(ambassador, 1, 1, 0, &testGame, 0, 0);
	if(returnVal != -1)
	{
		printf("cardEffect function return 0 without error.\n");
	}
	else
	{
		printf("cardEffect function return -1 with error.\n");
	}
	
	printf("cardEffect functin should return -1 with error.\n");
	newAssertEqualInt(returnVal, -1, "return value from cardEffect");
}