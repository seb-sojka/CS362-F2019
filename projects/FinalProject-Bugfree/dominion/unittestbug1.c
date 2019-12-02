//unittestbug2.c tests Mine card

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
	G.hand[player][1] = copper; 
	G.hand[player][2] = estate; 
	G.hand[player][3] = estate;
	G.hand[player][4] = estate;
	
	//Test 1 is to check to see if copper treasure card is being trashed.
	//In order to test if treasure card is being trashed we need to make 
	//all the if statements pass.
	printf("\n\nTEST 1: Check if copper is trashed or discarded");
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
	int returnValue = cardEffect(mine, 1, gold, -1, &G, 0, 0); 
	
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
	printf("\nTEST 1 RESULTS for Bug 1\n\n");
	assert(-1, returnValue, "Return value should be -1");
	assert(4, G.handCount[player], "Player's handCount should be four.");
	assert(0, G.discardCount[player], "Player's discard pile should be zero.");
	assert(3, getCost(copper)+3, "Cost of copper card to trash + 3 should be three.");
	assert(6, getCost(gold), "Cost of gold card to gain should be six");

	return 0;
}