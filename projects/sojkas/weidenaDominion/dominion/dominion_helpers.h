#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int callMine(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);
int callBaron(int choice1, struct gameState *state, int handPos, int currentPlayer);
int callMinion(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);
int callTribute(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer, int nextPlayer);
int callAmbassador(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);
int addTributeCard(int tributeRevealedCards, struct gameState *state, int nextPlayer);
int discardHand(int handPos, struct gameState *state, int currentPlayer);
int drawXCards(struct gameState *state, int numCards, int currentPlayer);
int gainEstate(struct gameState *state, int currentPlayer);
int greaterThanCheck(int opt1, int opt2);
int lessThanCheck(int opt1, int opt2);


#endif
