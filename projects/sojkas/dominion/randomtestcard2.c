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

#define TESTCARD "minion"

#define TESTLIMIT 100000
#define NUMBUYSINCREASE 0
#define ACTIONINCREASE 1
#define INCREASECOINS 2
#define NEWHANDCOUNT 4
//Discard count after baron when not discard estate
#define DISCARDNUM 1

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

void setUpRandomGame(struct gameState* game, int* handPos)
{
	*handPos = -1;
	int seed = rand();
	int k[10];
	//Limit cards in play to the cards avialbe to choose from and do not duplicate them.
	int j = 1;
	int i = 0;
	k[0] = minion;
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
			if(i == currentPlayer && game->hand[i][j] == minion && *handPos < 0)
			{
				*handPos = j;
			}
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
	if(*handPos < 0)
	{
		*handPos = rand() % game->handCount[currentPlayer];
		game->hand[currentPlayer][*handPos] = minion;
	}
	//Number of coins and number of buys random between 0 and 100
	//Number of number actions is between 1 and 100 as the card to be played
	game->numActions = (rand() % 99) + 1;
	game->coins = rand() % 100;
	game->numBuys = rand() % 100;
}


void checkPlayersHand(struct gameState testGame, struct gameState game, int gainCoins)
{
	int i;
	if(gainCoins)
	{
		for(i = 0; i < testGame.numPlayers; i++)
		{
			if(i != testGame.whoseTurn)
			{
				printf("player %d hand count = %d, expected = %d\n", i, testGame.handCount[i], game.handCount[i]);
				newAssertEqualInt(testGame.handCount[i], game.handCount[i], i + " player hand count");
				printf("player %d discard count = %d, expected = %d\n", i, testGame.discardCount[i], game.discardCount[i]);
				newAssertEqualInt(testGame.discardCount[i], game.discardCount[i], i + " player discard count");
			}
		}
	}
	else
	{
		for(i = 0; i < testGame.numPlayers; i++)
		{
			if(i != testGame.whoseTurn)
			{
				if(game.handCount[i] >= 5)
				{
					printf("player %d hand count = %d, expected = %d\n", i, testGame.handCount[i], NEWHANDCOUNT);
					newAssertEqualInt(testGame.handCount[i], NEWHANDCOUNT, "current player hand count");
					printf("player %d discard count = %d, expected = %d\n", i, testGame.discardCount[i], game.discardCount[i] + game.handCount[i]);
					newAssertEqualInt(testGame.discardCount[i], game.discardCount[i] + game.handCount[i], i + " player discard count");
				}
				else
				{
					printf("player %d hand count = %d, expected = %d\n", i, testGame.handCount[i], game.handCount[i]);
					newAssertEqualInt(testGame.handCount[i], game.handCount[i], i + " player hand count");
					printf("player %d discard count = %d, expected = %d\n", i, testGame.discardCount[i], game.discardCount[i]);
					newAssertEqualInt(testGame.discardCount[i], game.discardCount[i], i + " player discard count");
				}
			}
		}
	}
}

int main() 
{
	printf("Testing Card is %s\n", TESTCARD);

	srand(time(NULL));
	int i;
	struct gameState game, testGame;
	int handPos = 0;
	for(i = 0; i < TESTLIMIT; i++)
	{
		printf("Test %d\n", i);
		memset(&game, 0, sizeof(struct gameState));
		memset(&testGame, 0, sizeof(struct gameState));
		setUpRandomGame(&game, &handPos);
		memcpy(&testGame, &game, sizeof(struct gameState));
		//Does player try to discard an easte or not.
		int gainCoins = rand() % 2;
		int currentPlayer = game.whoseTurn;
		minionEffect(gainCoins, &testGame, currentPlayer, handPos);
		//Estate to discard
		if(gainCoins == 1)
		{
			printf("Coins Gained\n");
			printf("current player coin count = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS);
			newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS, "current player coin count");
			printf("current player hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUM);
			newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUM, "current player hand count");
			printf("current player discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + DISCARDNUM);
			newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + DISCARDNUM, "current player discard count");
			printf("played Card Count = %d, expected = %d\n", testGame.playedCardCount, game.playedCardCount + 1);
			newAssertEqualInt(testGame.playedCardCount, game.playedCardCount + 1, "played Card Count");
			checkPlayersHand(testGame, game, gainCoins);
		}
		//Either choice not to discard an estate or does not have one
		else
		{
			printf("Discard Hand\n");
			printf("current player coin count = %d, expected = %d\n", testGame.coins, game.coins);
			newAssertEqualInt(testGame.coins, game.coins, "current player coin count");
			printf("current player hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], NEWHANDCOUNT);
			newAssertEqualInt(testGame.handCount[currentPlayer], NEWHANDCOUNT, "current player hand count");
			printf("current player discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + game.handCount[currentPlayer] + DISCARDNUM);
			newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + game.handCount[currentPlayer] + DISCARDNUM, "current player discard count");
			printf("played Card Count = %d, expected = %d\n", testGame.playedCardCount, game.playedCardCount + 1);
			newAssertEqualInt(testGame.playedCardCount, game.playedCardCount + 1, "played Card Count");
			printf("Minion is expected to be discarded\n");
			checkPlayersHand(testGame, game, gainCoins);
		}
		printf("Minion is expected to be discarded\n");
		printf("Number actions = %d, expected = %d\n", testGame.numActions, game.numActions + ACTIONINCREASE);
		newAssertEqualInt(testGame.numActions, game.numActions + ACTIONINCREASE, "Number actions");
		printf("buy count = %d, expected = %d\n", testGame.numBuys, game.numBuys);
		newAssertEqualInt(testGame.numBuys, game.numBuys, "buy count");
	}
}