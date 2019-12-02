  
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


void assertTrue(int test, int value) {
	if (test == value) {
		printf("PASSED\t");
	}
	else {
		printf("FAILED\t");
	}
}



int testFeast(int expectedCase, struct gameState *state) {

        int val, expectedCoins;
        int expectedVal = 0;

        // make sure there are estates (worth 2),duchy's (worth 5) and providences (worth 8) to choose from
        state->supplyCount[estate] = 10;
        state->supplyCount[duchy] = 10;
        state->supplyCount[province] = 10;

        // set whose turn to 0th player
        state->whoseTurn = 0;

        // add coins to the hand (this is how updateCoins works)
        state->hand[0][0] = silver;
        state->hand[0][1] = gold;
        state->hand[0][2] = silver;
        state->hand[0][3] = gold;
        state->handCount[0] = 4;
        updateCoins(0, state, 0);
        expectedCoins = state->coins;

        // value of card less than 5
        if (expectedCase == 0)        
		{
            val = cardEffect(feast, estate, 0, 0, state, 0, 0);
            printf("CASE: Value of chosen card is less than 5\n");
            assertTrue(expectedVal, val);
		    printf("TEST: cardEffect returns 0.\n");
            assertTrue(expectedCoins, state->coins);
		    printf("TEST: player's coins have not changed.\n");


        }

        // value of card more than 5
        /*else if (expectedCase == 1)        
		{
            val = cardEffect(feast, province, 0, 0, state, 0, 0);
            printf("CASE: Value of chosen card is greater than 5\n");
            assertTrue(expectedVal, val);
		    printf("TEST: cardEffect returns -1.\n");
            assertTrue(expectedCoins, state->coins);
		    printf("TEST: player's coins have not changed.\n");

        }*/

        // value of card equal to 5
        else if (expectedCase == 1)        
		{
            val = cardEffect(feast, duchy, 0, 0, state, 0, 0);
            printf("CASE: Value of chosen card is equal to 5\n");
            assertTrue(expectedVal, val);
		    printf("TEST: cardEffect returns 0.\n");
            assertTrue(expectedCoins, state->coins);
		    printf("TEST: player's coins have not changed.\n");

        }

        // player does not have any coins currently in hand
        else if (expectedCase == 2)
        {
            for (int i =0; i<4; i++)
            {
                state->hand[0][i] = estate;
            }
            updateCoins(0, state, 0);
            expectedCoins = state->coins;
            printf("CASE: Player does not currently have any coins in their hand and value of card is 5\n");
            val = cardEffect(feast, duchy, 0, 0, state, 0, 0);
            assertTrue(expectedVal, val);
		    printf("TEST: cardEffect returns 0.\n");
            assertTrue(expectedCoins, state->coins);
		    printf("TEST: player's coins have not changed.\n");
        }

        // value of cards in hand is equal to 5
        else
        {
            state->handCount[0] = 2;
            updateCoins(0, state, 0);
            expectedCoins = state->coins;
            printf("CASE: Player currently has 5 coins in their hand and value of card is 5\n");
            val = cardEffect(feast, duchy, 0, 0, state, 0, 0);
            assertTrue(expectedVal, val);
		    printf("TEST: cardEffect returns 0.\n");
            assertTrue(expectedCoins, state->coins);
		    printf("TEST: player's coins have not changed.\n");
        }
        

	return val;
}

int main (int argc, char** argv)	
{
    struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));

	printf("Tests for scoreFor\n");

	//hard coded tests
	for(int i = 0; i < 10; i++){
		int seed = rand() % 1000;
		int expectedCase = rand() % 4;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		testFeast(expectedCase, &G);
	}

	return 0;

}