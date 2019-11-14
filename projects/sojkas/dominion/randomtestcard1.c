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

#define TESTLIMIT 10
#define NUMBUYSINCREASE 1
#define INCREASECOINS 4
#define DRAWCARDS 2
#define GAINACTIONS 2

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

void valueInArray(int val, int array[])
{
	int i;
	for(i = 0; i < sizeof(array) / sizeof(array[0]); i++)
    {
        if(array[i] == val)
            return 1;
    }
	return 0;
}

int main() 
{
	srand(time(NULL));
	int seed = rand();
	int i, j;
	
	int k[10];
	for(i = 0; i < TESTLIMIT; i++)
	{
		//Limit cards in play to the cards avialbe to choose from and do not duplicate them.
		j = 0;
		while(j < 10)
		{
			int newCard = rand() % 20 + 7;
			if(!valueInArray())
			{
				k[j] = newCard;
				j++;
			}
			
		}
		//Limit number of players from 2 to 4 for testing as that is the limit of players
		int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
		int currentPlayer =  rand() % numPlayers;
	}
	
	
	

}