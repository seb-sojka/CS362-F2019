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
#define NUMBUYSINCREASE 1
#define INCREASECOINS 4
//Discard count after baron when discard estate
#define DISCARDNUMESTATE 2
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

void setUpRandomGame(struct gameState* game, int* estateInHand)
{
	*estateInHand = 0;
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
			if(i == currentPlayer && game->hand[i][j] == estate)
			{
				*estateInHand = 1;
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
	//Number of coins and number of buys random between 0 and 100
	//Number of number actions is between 1 and 100 as the card to be played
	game->numActions = (rand() % 99) + 1;
	game->coins = rand() % 100;
	game->numBuys = rand() % 100;
}

int main() 
{
	printf("Testing Card is %s\n", TESTCARD);

	int estateInHand = 0;
	srand(time(NULL));
	int i;
	struct gameState game, testGame;
	for(i = 0; i < TESTLIMIT; i++)
	{
		printf("Test %d\n", i);
		memset(&game, 0, sizeof(struct gameState));
		memset(&testGame, 0, sizeof(struct gameState));
		setUpRandomGame(&game, &estateInHand);
		memcpy(&testGame, &game, sizeof(struct gameState));
		//Does player try to discard an easte or not.
		int choiceDiscard = rand() % 2;
		int currentPlayer = game.whoseTurn;
		baronEffect(choiceDiscard, &testGame, currentPlayer);
		//Estate to discard
		if(choiceDiscard == 1 && estateInHand == 1)
		{
			printf("Estate Discarded\n");
			printf("current player coin count = %d, expected = %d\n", testGame.coins, game.coins + INCREASECOINS);
			newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS, "current player coin count");
			printf("Number actions = %d, expected = %d\n", testGame.numActions, game.numActions);
			newAssertEqualInt(testGame.numActions, game.numActions, "Number actions");
			printf("current player hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUMESTATE);
			newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUMESTATE, "current player hand count");
			printf("current player discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + DISCARDNUMESTATE);
			newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + DISCARDNUMESTATE, "current player discard count");
			printf("played Card Count = %d, expected = %d\n", testGame.playedCardCount, game.playedCardCount + 1);
			newAssertEqualInt(testGame.playedCardCount, game.playedCardCount + 1, "played Card Count");
			printf("Estate is expected to be discarded\n");
			if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] == estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == estate)
			{
				printf("The estate is in discarded\n");
				printf("INFO: Test Success for baron being in the discard.\n");

			}
			else
			{
				printf("The estate is not in discarded\n");
				printf("ERROR: Test FAILURE for estate being in the discard.\n");
			}
			printf("Baron is expected to be discarded\n");
			if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] == baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == baron)
			{
				printf("The baron is in discard\n");
				printf("INFO: Test Success for baron being in the discard.\n");

			}
			else
			{
				printf("The baron is not in discard\n");
				printf("ERROR: Test FAILURE for baron being in the discard.\n");
			}
			printf("Estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate]);
			newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate], "Estate Play count");
		}
		//Either choice not to discard an estate or does not have one
		else
		{
			printf("Estate Gained\n");
			printf("current player coin count = %d, expected = %d\n", testGame.coins, game.coins);
			newAssertEqualInt(testGame.coins, game.coins + INCREASECOINS, "current player coin count");
			printf("Number actions = %d, expected = %d\n", testGame.numActions, game.numActions);
			newAssertEqualInt(testGame.numActions, game.numActions, "Number actions");
			printf("current player hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUM);
			newAssertEqualInt(testGame.handCount[currentPlayer], game.handCount[currentPlayer] - DISCARDNUM, "current player hand count");
			//It is plus 2 for discard count as an estate is gained along with discard the played baron
			printf("current player discard count = %d, expected = %d\n", testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + 2);
			newAssertEqualInt(testGame.discardCount[currentPlayer], game.discardCount[currentPlayer] + 2, "current player discard count");
			printf("played Card Count = %d, expected = %d\n", testGame.playedCardCount, game.playedCardCount + 1);
			newAssertEqualInt(testGame.playedCardCount, game.playedCardCount + 1, "played Card Count");
			if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] == estate || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == estate)
			{
				printf("The estate is in discarded\n");
				printf("INFO: Test Success for baron being in the discard.\n");

			}
			else
			{
				printf("The estate is not in discarded\n");
				printf("ERROR: Test FAILURE for estate being in the discard.\n");
			}
			printf("Baron is expected to be discarded\n");
			if(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] == baron || testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == baron)
			{
				printf("The baron is in discard\n");
				printf("INFO: Test Success for baron being in the discard.\n");

			}
			else
			{
				printf("The baron is not in discard\n");
				printf("ERROR: Test FAILURE for baron being in the discard.\n");
			}
			printf("Baron is expected to be discarded\n");
			printf("Estate supply count = %d, expected = %d\n", testGame.supplyCount[estate], game.supplyCount[estate] - 1);
			if(game.supplyCount[estate] != 0)
			{
				newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate] - 1, "Estate Play count");
			}
			else
			{
				newAssertEqualInt(testGame.supplyCount[estate], game.supplyCount[estate], "Estate Play count");
			}
		}
		printf("buy count = %d, expected = %d\n", testGame.numBuys, game.numBuys + 1);
		newAssertEqualInt(testGame.numBuys, game.numBuys + 1, "buy count");
	}
}