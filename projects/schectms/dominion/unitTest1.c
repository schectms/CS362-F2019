#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#undef assert

#define TESTCARD "baron"

int x;
#define assert(x) {if (x == 0) printf("Test Failed\n"); else printf("Test Passed\n");}

int main() {

	//initialize variables for testing
	int discarded = 0;
	int xtraCoins = 0;
	int extraBuys = 1;
	int estateGained = 0;
	int extraCard = 0;
	int shuffledCards = 0;

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
	printf("TEST 1: CHOICE 1:1 ESTATE DISCARDED, +4 COINS\n");


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	G.hand[thisPlayer][0] = estate;
	playBaron(&testG, choice1, thisPlayer);

	xtraCoins = 4;
	discarded = 2;
	int estateFound = 0;
	int estateDiscarded = -1; //tracks the discarded card
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

	assert(testG.supplyCount[estate] == testG.supplyCount[estate]);
	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numBuys == G.numBuys + extraBuys);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(correctDiscard);

	printf("\n");

	// ----------- TEST 2: CHOICE 1:1 NO AVAILABLE ESTATES - ESTATE GAINED--------------
	printf("TEST 2: CHOICE 1:1 NO AVAILABLE ESTATES - ESTATE GAINED\n");

	//this test checks what will happen if an estate card is not avail to be discarded
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		if (G.hand[thisPlayer][i] == estate)
		{
			G.hand[thisPlayer][i] = baron;
		}
	}

	G.supplyCount[estate] = 2;

	choice1 = 1;
	xtraCoins = 0;
	estateGained = 1;
	extraCard = 1;
	discarded = 1;

	memcpy(&testG, &G, sizeof(struct gameState));

	playBaron(&testG, choice1, thisPlayer);

	estateFound = 0;
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == estate)
		{
			estateFound = 1;
			break;
		}
	}

	assert(testG.supplyCount[estate] == testG.supplyCount[estate] - estateGained);
	assert((testG.coins == G.coins + xtraCoins));
	assert(testG.numBuys == G.numBuys + extraBuys);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + extraCard - discarded);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(estateFound);

	printf("\n");

	// ----------- TEST 3 CHOICE 1:0 ESTATE GAINED--------------
	printf("TEST 3 CHOICE 1:0 ESTATE GAINED\n");

	G.supplyCount[estate] = 1;

	choice1 = 0;
	xtraCoins = 0;
	estateGained = 1;
	extraCard = 1;
	discarded = 1;

	memcpy(&testG, &G, sizeof(struct gameState));

	playBaron(&testG, choice1, thisPlayer);

	estateFound = 0;
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == estate)
		{
			estateFound = 1;
			break;
		}
	}

	assert(testG.supplyCount[estate] == testG.supplyCount[estate] - estateGained);
	assert((testG.coins == G.coins + xtraCoins));
	assert(testG.numBuys == G.numBuys + extraBuys);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + extraCard - discarded);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(estateFound);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
