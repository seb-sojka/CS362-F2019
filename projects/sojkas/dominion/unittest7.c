  
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



int testTribute(int expectedCase, struct gameState *state) {

        int val, expectedActions;

        // add tribute to hand
        state->hand[0][0] = tribute;
        state->handCount[0]++;

        // hand with two revealed action cards
        if (expectedCase == 0)        
		{
            state->deck[0][0] = feast;
            state->deck[0][1] = mine;
            state->deck[0][2] = tribute;
            state->deck[0][3] = baron;
            state->deck[0][4] = minion;
            state->deckCount[0] = 5;
            state->numActions = 1;
            expectedActions = state->numActions + 4;
            val = tributeEffect(state, 0);
            printf("CASE: Two action cards are revealed\n");
            assertTrue(expectedActions, state->numActions);
		    printf("TEST: expected number of actions are %d\n", expectedActions);


        }

        // one action card is revelaed
        else if (expectedCase == 1)        
		{
            state->deck[0][0] = estate;
            state->deck[0][1] = estate;
            state->deck[0][2] = estate;
            state->deck[0][3] = estate;
            state->deck[0][4] = minion;
            state->deckCount[0] = 5;
            state->numActions = 1;
            expectedActions = state->numActions + 2;
            val = tributeEffect(state, 0);
            printf("CASE: One action card is revealed\n");
            assertTrue(expectedActions, state->numActions);
		    printf("TEST: expected number of actions are %d\n", expectedActions);

        }

        // no action card is revealed
        else
        {
            state->deck[0][0] = duchy;
            state->deck[0][1] = silver;
            state->deck[0][2] = gold;
            state->deck[0][3] = province;
            state->deck[0][4] = estate;
            state->deckCount[0] = 5;
            state->numActions = 1;
            expectedActions = state->numActions;
            val = tributeEffect(state, 0);
            printf("CASE: No action cards are revealed\n");
            assertTrue(expectedActions, state->numActions);
		    printf("TEST: expected number of actions are %d\n", expectedActions);
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
		int expectedCase = rand() % 5;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		testTribute(expectedCase, &G);
	}

	return 0;

}