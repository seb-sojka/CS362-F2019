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

#define TESTCARD "cardEffect"

#define TESTLIMIT 10000

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
	int k[10];
	//Limit cards in play to the cards avialbe to choose from and do not duplicate them.
	int j = 0;
	int i = 0;
	while(j < 10)
	{
		int newCard = rand() % 20 + 7;
		if(!valueInArray(newCard, k))
		{
			k[j] = newCard;
			j++;
		}
		
	}
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
	game->playedCardCount = rand() % (MAX_DECK + 1);
	for(i = 0; i < game->playedCardCount; i++)
	{
		game->playedCards[i] = allCards[rand()%17];
	}
	for(i = 0; i < numPlayers; i++)
	{
		//Set hand size of players. Current player needs at least 1 card in hand to play.
		//All players have a hand limit of 500.
		if(i == currentPlayer)
		{
			game->handCount[i] = rand()% (MAX_HAND) + 1;
		}
		else
		{
			game->handCount[i] = rand()% (MAX_HAND + 1);
		}
		//Set deck size of players up to 500 as limited in the code
		game->deckCount[i] = rand()% (MAX_HAND + 1);
		//Set discard pile size of players up to 500 as limited in the code
		game->discardCount[i] = rand() % (MAX_DECK + 1);
		
		//Set deck, discard, aand deck to random cards in play
		for(j = 0; j < game->handCount[i]; j++)
		{
			game->hand[i][j] = allCards[rand()%17];
		}
		for(j = 0; j < game->deckCount[i]; j++)
		{
			game->deck[i][j] = allCards[rand()%17];
		}
		for(j = 0; j < game->discardCount[i]; j++)
		{
			game->discard[i][j] = allCards[rand()%17];
		}
	}
	
	//Set supply count from its startig supply to 0.
	for (i = 0; i < 27; i++)
	{
		if(game->supplyCount[i] > -1 && i != copper)
		{
			game->supplyCount[i] = rand() % (game->supplyCount[i] + 1);
		}
		else if(i == copper)
		{
			game->supplyCount[i] = rand() % 60;
		}
	}
	//Number of coins and number of buys random between 0 and 100
	//Number of number actions is between 1 and 100 as the card to be played
	game->numActions = (rand() % 99) + 1;
	game->coins = rand() % 100;
	game->numBuys = rand() % 100;
}

int main() 
{
	printf("Testing Card is %s\n", TESTCARD);
	srand(time(NULL));
	struct gameState game, testGame;
	printf("Test 1: Gain Coins from Baron card\n");
	memset(&game, 0, sizeof(struct gameState));
	memset(&testGame, 0, sizeof(struct gameState));
	setUpRandomGame(&game);
	game.hand[game.whoseTurn][0] = baron;
	game.hand[game.whoseTurn][1] = estate;
	memcpy(&testGame, &game, sizeof(struct gameState));
	playCard(0, 1, 0, 0, &testGame);
	updateCoins(game.whoseTurn, &game, 0);
	printf("coin Count = %d, expected = %d\n", testGame.coins, game.coins + 4);
	newAssertEqualInt(testGame.coins, game.coins + 4, "played Card Count");
	printf("Test 2: Gain Coins from minion  card\n");
	memset(&game, 0, sizeof(struct gameState));
	memset(&testGame, 0, sizeof(struct gameState));
	setUpRandomGame(&game);
	game.hand[game.whoseTurn][0] = minion;
	memcpy(&testGame, &game, sizeof(struct gameState));
	playCard(0, 1, 0, 0, &testGame);
	updateCoins(game.whoseTurn, &game, 0);
	printf("coin Count = %d, expected = %d\n", testGame.coins, game.coins + 2);
	newAssertEqualInt(testGame.coins, game.coins + 2, "played Card Count");
	printf("Test 3: Gain Coins from steward  card\n");
	memset(&game, 0, sizeof(struct gameState));
	memset(&testGame, 0, sizeof(struct gameState));
	setUpRandomGame(&game);
	game.hand[game.whoseTurn][0] = steward;
	memcpy(&testGame, &game, sizeof(struct gameState));
	playCard(0, 2, 0, 0, &testGame);
	updateCoins(game.whoseTurn, &game, 0);
	printf("coin Count = %d, expected = %d\n", testGame.coins, game.coins + 2);
	newAssertEqualInt(testGame.coins, game.coins + 2, "played Card Count");
	printf("Test 4: Gain Coins from embargo card\n");
	memset(&game, 0, sizeof(struct gameState));
	memset(&testGame, 0, sizeof(struct gameState));
	setUpRandomGame(&game);
	game.hand[game.whoseTurn][0] = embargo;
	memcpy(&testGame, &game, sizeof(struct gameState));
	playCard(0, copper, 0, 0, &testGame);
	updateCoins(game.whoseTurn, &game, 0);
	printf("coin Count = %d, expected = %d\n", testGame.coins, game.coins + 2);
	newAssertEqualInt(testGame.coins, game.coins + 2, "played Card Count");
	printf("\n\n");
	
}
