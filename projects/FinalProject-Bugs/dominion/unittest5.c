  
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

int testScoreFor(int expectedCase, struct gameState *state) {

        int val, i;
        int expectedVal = 0;

        // set each count to 0
        state->handCount[0] = 0;
        state->deckCount[0] = 0;
        state->discardCount[0] = 0;

        // add known amount to hand
        for (i = 0; i <5; i++)
        {
            state->hand[0][i] = estate;
            state->handCount[0]++;
            expectedVal++;

        }

        // discard less than deck
        if (expectedCase == 0)        
		{
            for (i = 0; i <5; i++)
            {
                state->discard[0][i] = estate;
                state->discardCount[0]++;
                expectedVal++;
            }

            for (i = 0; i <10; i++)
            {
                state->deck[0][i] = estate;
                state->deckCount[0]++;
                expectedVal++;
            }

        }

        // discard more than deck
        else if (expectedCase == 1)        
		{
            for (i = 0; i <10; i++)
            {
                state->discard[0][i] = estate;
                state->discardCount[0]++;
                expectedVal++;
            }

            for (i = 0; i <5; i++)
            {
                state->deck[0][i] = estate;
                state->deckCount[0]++;
                expectedVal++;
            }

        }

        //discard same as deck
        else
        {
            for (i = 0; i <10; i++)
            {
                state->discard[0][i] = estate;
                state->discardCount[0]++;
                expectedVal++;
            }

            for (i = 0; i <10; i++)
            {
                state->deck[0][i] = estate;
                state->deckCount[0]++;
                expectedVal++;
            }
        }
        
        // call scoreFor
		val = scoreFor(0, state);

		if(expectedCase == 0)
		{
			printf("CASE: There are more cards in the deck than the discard, expected score is %d\n", expectedVal);
		}

		else if(expectedCase == 1)
		{
			printf("CASE: There are more cards in the discard than the deck, expected score is %d\n", expectedVal);
		}

		else{
			printf("CASE: There are equal cards in the discard and deck, expected score is %d\n", expectedVal);
		}

		assertTrue(expectedVal, val);
		printf("TEST: scoreFor returns correct score.\n");

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
		int expectedCase = rand() % 3;
		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);

		testScoreFor(expectedCase, &G);
	}

	return 0;

}