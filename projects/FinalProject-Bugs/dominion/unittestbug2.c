//unittestbug1.c tests Mine card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int assert(int expected, int actual , char* string)
{
	if(expected == actual)
	{
		printf("PASSED: Expected:%d  Actual:%d -- %s\n", expected, actual, string);
		return 0;
	}
	else
	{
		printf("FAILED: Expected:%d  Actual:%d -- %s\n", expected, actual, string);
	} 
	return 1;
}

int main()
{
	srand(time(0));
	int player = 0;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	//set game state and initialize new game
	memset(&G, 1, sizeof(struct gameState)); 
	initializeGame(2, k, rand(), &G);

	//set player's hand
	G.hand[player][0] = mine; 
	G.hand[player][1] = silver; 
	G.hand[player][2] = estate; 
	G.hand[player][3] = estate;
	G.hand[player][4] = estate;
	
	//Test 1 is to trash a silver treasure card and gain a silver treasure card
	//Will fail since the getCost if statement is not corret
	printf("\nTEST 1: Trash silver, gain silver\n");
	//pre game state
	printf("\nBEFORE CARDEFFECT CALL\n");
	printf("Player's handCount: %d\n", G.handCount[player]);
	printf("Player's discardCount: %d\n\n", G.discardCount[player]);
	
	printf("Cards in player's hand: ");
	for(int i = 0; i < G.handCount[player]; i++)
	{
		printf("%d ", G.hand[player][i]);
	}
	printf("\n");
	printf("Cards in player's discard pile: ");
	for(int i = 0; i < G.discardCount[player]; i++)
	{
		printf("%d ", G.discard[player][i]);
	}
	printf("\n");
	printf("Cards in player's played pile: ");
	for(int i = 0; i < G.playedCards[i]; i++)
	{
		printf("%d ", G.playedCards[i]);
	}
	printf("\n");
	
	//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
	int returnValue = cardEffect(mine, 1, silver, -1, &G, 0, 0); 
	
	//after game state
	printf("\nAFTER CARDEFFECT CALL\n");
	printf("Player's handCount: %d\n", G.handCount[player]);
	printf("Player's discardCount: %d\n\n", G.discardCount[player]);
	
	printf("Cards in player's hand: ");
	for(int i = 0; i < G.handCount[player]; i++)
	{
		printf("%d ", G.hand[player][i]);
	}
	printf("\n");
	printf("Cards in player's discard pile: ");
	for(int i = 0; i < G.discardCount[player]; i++)
	{
		printf("%d ", G.discard[player][i]);
	}
	printf("\n");
	printf("Cards in player's played pile: ");
	for(int i = 0; i < G.playedCards[i]; i++)
	{
		printf("%d ", G.playedCards[i]);
	}
	printf("\n");

	//Assertions and results
	printf("\nTEST 1 RESULTS for Bug 2\n\n");
	assert(0, returnValue, "Return value should be zero");
	assert(4, G.handCount[player], "Player's handCount should be four.");
	assert(0, G.discardCount[player], "Player's discard pile should be zero.");
	assert(6, getCost(silver)+3, "Cost of silver card to trash + 3 should be six.");
	assert(3, getCost(silver), "Cost of silver card to gain is three");
	
	//set game state and initialize new game
	memset(&G, 1, sizeof(struct gameState)); 
	initializeGame(2, k, rand(), &G);

	//set player's hand
	G.hand[player][0] = mine; 
	G.hand[player][1] = copper; 
	G.hand[player][2] = estate; 
	G.hand[player][3] = estate;
	G.hand[player][4] = estate;
	
	//Test 2 is to trash a copper treasure card and gain a silver treasure card
	printf("\n\nTEST 2: Trash copper, gain silver\n");
	//pre game state
	printf("\nBEFORE CARDEFFECT CALL\n");
	printf("Player's handCount: %d\n", G.handCount[player]);
	printf("Player's discardCount: %d\n\n", G.discardCount[player]);
	
	printf("Cards in player's hand: ");
	for(int i = 0; i < G.handCount[player]; i++)
	{
		printf("%d ", G.hand[player][i]);
	}
	printf("\n");
	printf("Cards in player's discard pile: ");
	for(int i = 0; i < G.discardCount[player]; i++)
	{
		printf("%d ", G.discard[player][i]);
	}
	printf("\n");
	printf("Cards in player's played pile: ");
	for(int i = 0; i < G.playedCards[i]; i++)
	{
		printf("%d ", G.playedCards[i]);
	}
	printf("\n");
	
	//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
	returnValue = cardEffect(mine, 1, silver, -1, &G, 0, 0); 
	
	//after game state
	printf("\nAFTER CARDEFFECT CALL\n");
	printf("Player's handCount: %d\n", G.handCount[player]);
	printf("Player's discardCount: %d\n\n", G.discardCount[player]);
	
	printf("Cards in player's hand: ");
	for(int i = 0; i < G.handCount[player]; i++)
	{
		printf("%d ", G.hand[player][i]);
	}
	printf("\n");
	printf("Cards in player's discard pile: ");
	for(int i = 0; i < G.discardCount[player]; i++)
	{
		printf("%d ", G.discard[player][i]);
	}
	printf("\n");
	printf("Cards in player's played pile: ");
	for(int i = 0; i < G.playedCards[i]; i++)
	{
		printf("%d ", G.playedCards[i]);
	}
	printf("\n");

	//Assertions and results
	printf("\nTEST 2 RESULTS for Bug 2\n\n");
	assert(0, returnValue, "Return value should be zero");
	assert(4, G.handCount[player], "Player's handCount should be four.");
	assert(0, G.discardCount[player], "Player's discard pile should be zero.");
	assert(3, getCost(copper)+3, "Cost of copper ./to trash + 3 should be three.");
	assert(3, getCost(silver), "Cost of silver card to gain is three");

	return 0;
}