#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

int main() {

	//initialize variables for testing
	int discarded = 2;
	int xtraCoins = 0;
	int extraBuys = 1;
	int estateGained = 0;
	int extraCard = 0;

	int i; //looping variable
	//initialize parameters for cardEffect
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 1;
	struct gameState G, testG; // set up structure for the game and the test
	//initialize available cards for deck
	int k[10] = { baron, estate, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 discard estate--------------
	printf("TEST 1: choice1 = 1 = discard estate\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	G.hand[thisPlayer][0] = estate;
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	int estateFound = 0;
	int estateDiscarded; //tracks the discarded card
	//check if an estate card is available
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		if (G.hand[thisPlayer][i] == estate)
		{
			estateFound = 1;
			estateDiscarded = G.hand[thisPlayer][i];
			break;
		}
	}

	//this test checks what will happen if an estate card is avail to be discarded
	printf("estate found and discarded + 4 coins\n");
	xtraCoins = 4;
	printf("estates left in supply= %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - estateGained);
	//assert(testG.supplyCount[estate]== G.supplyCount[estate] - estateGained);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	//assert(testG.coins== G.coins + xtraCoins);
	printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
	//assert(testG.numBuys== G.numBuys + extraBuys);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
	printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);


	printf("Has the estate been properly discarded?\n");
	int correctDiscard = 0;
	// tests that the removed cards are no longer in the player's hand
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == estateDiscarded)
		{
			printf("NO\n");
			break;
		}
		else
		{
			correctDiscard = 1;
		}
	}
	if (correctDiscard == 1) { printf("YES\n"); }
	//assert(correctDiscard==1);


	printf("\n");

	// ----------- TEST 2: choice2 = 1 discard estate (but no estate is available)--------------
	printf("TEST 2: choice1 = 1 = discard estate\n");
	//this test checks what will happen if an estate card is not avail to be discarded
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		if (G.hand[thisPlayer][i] == estate)
		{
			G.hand[thisPlayer][i] = baron;
		}
	}


	G.supplyCount[estate] = 2;

	memcpy(&testG, &G, sizeof(struct gameState));
	printf("no estate found-player will gain estate\n");
	choice1 = 1;
	xtraCoins = 0;
	estateGained = 1;
	extraCard = 1;
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("estates left in supply= %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - estateGained);
	//assert(testG.supplyCount[estate] == G.supplyCount[estate] - estateGained);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	//assert(testG.coins == G.coins + xtraCoins);
	printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
	//assert(testG.numBuys == G.numBuys + extraBuys);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + extraCard);
	printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);

	printf("\n");

	// ----------- TEST 3: choice1 = 0 gain estate--------------
	printf("TEST 3: choice1 = 0 = gain estate\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	xtraCoins = 0;
	estateGained = 1;
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("estates left in supply= %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - estateGained);
	//assert(testG.supplyCount[estate] == G.supplyCount[estate] - estateGained);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	//assert(testG.coins == G.coins + xtraCoins);
	printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
	//assert(testG.numBuys == G.numBuys + extraBuys);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + extraCard);
	printf("hand count next player = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
