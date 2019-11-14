/*
 * unittest2.c
 * To test the function for the tribute Card, tributeEffect.
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

#define TESTCARD "tribute"

#define CARDDISCARD 1
#define INCREASECOINS 2
#define DRAWCARDS 2
#define GAINACTIONS 2
#define TESTLIMIT 0

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
	int revealCards[] = {-1, -1};
	int treasuresRev = 0;
	int actionRev = 0;
	int victRev = 0;
    int seed = 1000;
	srand(time(NULL));
	int i;
    int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
    int currentPlayer =  rand() % numPlayers;
	int nextPlayer = currentPlayer + 1;
	if(nextPlayer >= numPlayers)
	{
		nextPlayer = 0;
	}
	int randHandSize = rand() % (MAX_HAND);
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

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}

	struct gameState game, testGame;

	printf("Testing Card is %s\n", TESTCARD);
	int testCount = 1;
	
	printf("TEST 1: Deck size of 1, Discard size of 1\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	randHandSize = rand() % (MAX_HAND);
	game.whoseTurn = currentPlayer;
	game.handCount[currentPlayer] = randHandSize;

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}
	
	revealCards[0] = -1;
	revealCards[1] = -1;
	for(i = 0; i < 2; i++)
	{
		revealCards[i] = rand() % 27;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
	
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);
	
	game.discardCount[nextPlayer] = 1;
	game.deckCount[nextPlayer] = 1;
	game.deck[nextPlayer][game.deckCount[nextPlayer] - 1] = revealCards[0];
	game.discard[nextPlayer][game.deckCount[nextPlayer] - 1] = revealCards[1];
	int triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
	printf("TEST 2: Deck size of 0, Discard size of 0\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;

	randHandSize = rand() % (MAX_HAND);
	game.handCount[currentPlayer] = randHandSize;

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}
	
	revealCards[0] = -1;
	revealCards[1] = -1;
	treasuresRev = 0;
	victRev = 0;
	actionRev = 0;

	
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);
	
	game.discardCount[nextPlayer] = 0;
	game.deckCount[nextPlayer] = 0;
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
	printf("TEST 3: Deck size of 0, Discard size of 2\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;

	randHandSize = rand() % (MAX_HAND);
	game.handCount[currentPlayer] = randHandSize;

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}
	
	revealCards[0] = -1;
	revealCards[1] = -1;
	for(i = 0; i < 2; i++)
	{
		revealCards[i] = rand() % 27;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
	
	printf("Card number to be revealed: %d\n", revealCards[0]);
	
	game.discardCount[nextPlayer] = 2;
	game.deckCount[nextPlayer] = 0;
	game.discard[nextPlayer][0] = revealCards[0];
	game.discard[nextPlayer][1] = revealCards[1];
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
	printf("TEST 4: Deck size of 0, Discard size of 1\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;

	randHandSize = rand() % (MAX_HAND);
	game.handCount[currentPlayer] = randHandSize;

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}
	
	revealCards[0] = -1;
	revealCards[1] = -1;
	for(i = 0; i < 1; i++)
	{
		revealCards[i] = rand() % 27;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
	
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);
	
	game.discardCount[nextPlayer] = 1;
	game.deckCount[nextPlayer] = 0;
	game.discard[nextPlayer][0] = revealCards[0];
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
	printf("TEST 5: Deck size of 1, Discard size of 0\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;

	randHandSize = rand() % (MAX_HAND);
	game.handCount[currentPlayer] = randHandSize;

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}
	
	revealCards[0] = -1;
	revealCards[1] = -1;
	for(i = 0; i < 1; i++)
	{
		revealCards[i] = rand() % 27;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
	
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);
	
	game.discardCount[nextPlayer] = 0;
	game.deckCount[nextPlayer] = 1;
	game.deck[nextPlayer][0] = revealCards[0];
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
	printf("TEST 6: Deck size of 2, Discard size of 0\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	randHandSize = rand() % (MAX_HAND);
	game.handCount[currentPlayer] = randHandSize;

	for(i = 0; i < randHandSize; i++)
	{
		newHand[i] = allCards[rand() % 17];
	}
	
	revealCards[0] = -1;
	revealCards[1] = -1;
	for(i = 0; i < 1; i++)
	{
		revealCards[i] = rand() % 27;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
	
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);
	
	game.discardCount[nextPlayer] = 0;
	game.deckCount[nextPlayer] = 2;
	game.deck[nextPlayer][0] = revealCards[0];
	game.deck[nextPlayer][1] = revealCards[1];
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	currentPlayer =  rand() % numPlayers ;
	nextPlayer = currentPlayer + 1;
	if(nextPlayer >= numPlayers)
	{
		nextPlayer = 0;
	}
	printf("TEST 8: Reveal only copper\n");
	treasuresRev = 0;
	actionRev = 0;
	victRev = 0;


	for(i = 0; i < 2; i++)
	{
		revealCards[i] = copper;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
		
		
		
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);

	game.deck[nextPlayer][game.deckCount[nextPlayer] - 1] = revealCards[0];
	game.deck[nextPlayer][game.deckCount[nextPlayer] - 2] = revealCards[1];
	game.handCount[currentPlayer] = randHandSize;
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	
		// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	game.whoseTurn = currentPlayer;
	currentPlayer =  rand() % numPlayers ;
	nextPlayer = currentPlayer + 1;
	if(nextPlayer >= numPlayers)
	{
		nextPlayer = 0;
	}
	printf("TEST 9: Reveal only silvers\n");
	treasuresRev = 0;
	actionRev = 0;
	victRev = 0;


	for(i = 0; i < 2; i++)
	{
		revealCards[i] = silver;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
		
		
		
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);

	game.deck[nextPlayer][game.deckCount[nextPlayer] - 1] = revealCards[0];
	game.deck[nextPlayer][game.deckCount[nextPlayer] - 2] = revealCards[1];
	game.handCount[currentPlayer] = randHandSize;
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");

	printf("TEST 10: Reveal only gold\n");
	treasuresRev = 0;
	actionRev = 0;
	victRev = 0;


	for(i = 0; i < 2; i++)
	{
		revealCards[i] = gold;
		printf("Card %d to be revealed: %d", i, revealCards[i]);
		if(revealCards[0] == revealCards[1])
		{
			printf("Card revealed to be the same\n");
		}
		else
		{
			if(revealCards[i] >= copper && revealCards[i] <= gold)
			{
				printf("Treasure to be revealed\n");
				treasuresRev++;
			}
			if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
			{
				printf("Victory card revealed\n");
				victRev++;
			}
			if (revealCards[i] > gold)
			{
				printf("Action card revealed\n");
				actionRev++;
			}
		}
	}
		
		
		
	printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);

	game.deck[nextPlayer][game.deckCount[nextPlayer] - 1] = revealCards[0];
	game.deck[nextPlayer][game.deckCount[nextPlayer] - 2] = revealCards[1];
	game.handCount[currentPlayer] = randHandSize;
	triPos = rand() % randHandSize;
	newHand[triPos] = tribute;
	memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
	memcpy(&testGame, &game, sizeof(struct gameState));
	tributeEffect(&testGame, triPos);
	
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
	printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
	printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
	newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	testCount = 11;
	for(;testCount < TESTLIMIT; testCount++)
	{
		numPlayers = rand() % (MAX_PLAYERS - 1) + 1;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &game);
		game.whoseTurn = currentPlayer;
		currentPlayer =  rand() % numPlayers ;
		nextPlayer = currentPlayer + 1;
		if(nextPlayer >= numPlayers)
		{
			nextPlayer = 0;
		}
		printf("TEST %d: Random test for reveal\n", testCount);
		treasuresRev = 0;
		actionRev = 0;
		victRev = 0;


		for(i = 0; i < 2; i++)
		{
			revealCards[i] = rand() % 27;
			printf("Card %d to be revealed: %d", i, revealCards[i]);
			if(revealCards[0] == revealCards[1])
			{
				printf("Card revealed to be the same\n");
			}
			else
			{
				if(revealCards[i] >= copper && revealCards[i] <= gold)
				{
					printf("Treasure to be revealed\n");
					treasuresRev++;
				}
				if (revealCards[i] == estate || revealCards[i] == duchy || revealCards[i] == province || revealCards[i] == great_hall)
				{
					printf("Victory card revealed\n");
					victRev++;
				}
				if (revealCards[i] > gold)
				{
					printf("Action card revealed\n");
					actionRev++;
				}
			}
		}
		
		
		
		printf("Card numbers to be revealed: %d & %d\n", revealCards[0], revealCards[1]);

		game.deck[nextPlayer][game.deckCount[nextPlayer] - 1] = revealCards[0];
		game.deck[nextPlayer][game.deckCount[nextPlayer] - 2] = revealCards[1];
		game.handCount[currentPlayer] = randHandSize;
		triPos = rand() % randHandSize;
		newHand[triPos] = tribute;
		memcpy(game.hand[currentPlayer], newHand, sizeof(int) * randHandSize);
		memcpy(&testGame, &game, sizeof(struct gameState));
		tributeEffect(&testGame, triPos);
		
		printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev);
		printf("coins gained = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * treasuresRev);
		printf("actions gained = %d, expected = %d\n", testGame.numActions, game.numActions + GAINACTIONS * actionRev);
		newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - CARDDISCARD + DRAWCARDS * victRev, "hand count");
		newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * treasuresRev, "coin count");
		newAssertEqualInt(testGame.numActions, game.numActions + GAINACTIONS * actionRev, "action count");
	}
}