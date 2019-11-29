/*
 * unittest8.c
 * To test the function Tribute and how bonus coins are treated from played cards 
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

#define TESTCARD "Tribute"

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

void setRevealCards(struct gameState* game, int card)
{
	int nextPlayer = game->whoseTurn + 1;
	if (game->numPlayers <= nextPlayer)
	{
		nextPlayer = 0;
	}
	game->deck[nextPlayer][game->deckCount[nextPlayer]-1] = card;
	game->deck[nextPlayer][game->deckCount[nextPlayer]-2] = card;
	
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
		game->deckCount[i] = rand()% (MAX_HAND - 1) + 2;
		//Set discard pile size of players up to 500 as limited in the code
		game->discardCount[i] = rand() % (MAX_DECK + 1);
		
		//Set deck, discard, aand deck to random cards in play
		for(j = 0; j < game->handCount[i]; j++)
		{
			game->hand[i][j] = allCards[rand()%17];
			if(i == currentPlayer && game->hand[i][j] == tribute && *handPos < 0)
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
	if(handPos < 0)
	{
		*handPos = rand() % game->handCount[currentPlayer];
		game->hand[currentPlayer][*handPos] = tribute;
	}
	int card = allCards[rand()%17];
	int nextPlayer = game->whoseTurn + 1;
	if (game->numPlayers <= nextPlayer)
	{
		nextPlayer = 0;
	}
	game->deck[nextPlayer][game->deckCount[nextPlayer]-1] = card;
	game->deck[nextPlayer][game->deckCount[nextPlayer]-2] = card;
	//Number of coins and number of buys random between 0 and 100
	//Number of number actions is between 1 and 100 as the card to be played
	game->numActions = (rand() % 99) + 1;
	game->coins = rand() % 100;
	game->numBuys = rand() % 100;
}

void getRevealCards(struct gameState game, int nextPlayer,int *numTreasure,int *numAction,int *numVictory)
{
	*numTreasure = 0;
	*numAction = 0;
	*numVictory = 0;
	int tributeRevealedCards[2] = { -1, -1 };
	int i;
	if (game.deckCount[nextPlayer] == 0)
	{
		for (i = 0; i < game.discardCount[nextPlayer]; i++) 
		{
			game.deck[nextPlayer][i] = game.discard[nextPlayer][i];//Move to deck
			game.deckCount[nextPlayer]++;
			game.discard[nextPlayer][i] = -1;
			game.discardCount[nextPlayer]--;
		}

		shuffle(nextPlayer, &game);//Shuffle the deck
	}
	tributeRevealedCards[0] = game.deck[nextPlayer][game.deckCount[nextPlayer] - 1];
	game.deck[nextPlayer][game.deckCount[nextPlayer]] = -1;
	game.deckCount[nextPlayer]--;
	if (game.deckCount[nextPlayer] == 0)
	{
		for (i = 0; i < game.discardCount[nextPlayer]; i++) 
		{
			game.deck[nextPlayer][i] = game.discard[nextPlayer][i];//Move to deck
			game.deckCount[nextPlayer]++;
			game.discard[nextPlayer][i] = -1;
			game.discardCount[nextPlayer]--;
		}
		shuffle(nextPlayer, &game);//Shuffle the deck
	}
	tributeRevealedCards[1] = game.deck[nextPlayer][game.deckCount[nextPlayer] - 1];

	if (tributeRevealedCards[0] == tributeRevealedCards[1]) //If we have a duplicate card, just drop one
	{
		tributeRevealedCards[1] = -1;
	}
	
	for (i = 0; i < 2; i++)
	{
		if(tributeRevealedCards[i] != -1)
		{
			printf("Card number revealed: %d\r\n", tributeRevealedCards[i]);
			if(tributeRevealedCards[i] <= gold && tributeRevealedCards[i] >= copper)
			{
				*numTreasure = *numTreasure + 1;
			}
			if((tributeRevealedCards[i] <= estate && tributeRevealedCards[i] >= province) || tributeRevealedCards[i] == great_hall)
			{
				*numVictory = *numVictory + 1;
			}
			if(tributeRevealedCards[i] > gold)
			{
				*numAction = *numAction + 1;
			}
		}
	}
}

int main() 
{
	printf("Testing Card is %s\n", TESTCARD);
	srand(time(NULL));
	struct gameState game, testGame;
	int numTreasure, numAction, numVictory;
	int handPos = 0;
	printf("Test 1: Same Card reveled from tribute\n");
	memset(&game, 0, sizeof(struct gameState));
	memset(&testGame, 0, sizeof(struct gameState));
	setUpRandomGame(&game, &handPos);
	int currentPlayer = game.whoseTurn;
	int nextPlayer = game.whoseTurn + 1;
	if(nextPlayer >= game.numPlayers)
	{
		nextPlayer = 0;
	}
	
	getRevealCards(game, nextPlayer, &numTreasure, &numAction, &numVictory);
	game.hand[game.whoseTurn][0] = tribute;
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(tribute, 0, 0, 0, &testGame, 0, 0);
	printf("next player card count = %d, expected = %d\n", testGame.deckCount[nextPlayer], game.deckCount[nextPlayer] - NUMBERCARDS);
	newAssertEqualInt(testGame.deckCount[nextPlayer], game.deckCount[nextPlayer] - NUMBERCARDS, "next player card count");
	printf("next player discard count = %d, expected = %d\n", testGame.discardCount[nextPlayer], game.discardCount[nextPlayer] + NUMBERCARDS);
	newAssertEqualInt(testGame.discardCount[nextPlayer], game.discardCount[nextPlayer] + NUMBERCARDS, "next player card count");
	printf("current player coin count = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS * numTreasure);
	newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS * numTreasure, "current player coin count");
	printf("Number actions = %d, expected = %d\n", testGame.numActions, game.numActions + ACTIONINCREASE * numAction);
	newAssertEqualInt(testGame.numActions, game.numActions + ACTIONINCREASE * numAction, "Number actions");
	printf("buy count = %d, expected = %d\n", testGame.numBuys, game.numBuys);
	newAssertEqualInt(testGame.numBuys, game.numBuys, "buy count");
	printf("current player hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUM + DRAWCARDS * numVictory);
	newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUM + DRAWCARDS * numVictory, "current player hand count");
}