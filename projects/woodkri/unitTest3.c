#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "ambassador"

int x;
#define assert(x) {if (x == 0) printf("Test Failed\n"); else printf("Test Passed\n");}

int main() {

	//initialize variables for testing
	int discarded = 0;
	int xtraCoins = 0;
	int extraBuys = 1;
	int estateGained = 0;

	int i; //looping variable
	//initialize parameters for cardEffect
	int handpos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;
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

	// ----------- TEST 1: CHOICE 2 >2--------------
	printf("TEST 1: CHOICE 2 > 2 INVALID NO CHANGE \n");
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = curse;
	choice2 = 3;
	int d = G.hand[thisPlayer][choice1];
	cardEffectAmbassador(choice1, choice2, &testG, handpos, thisPlayer);
	assert(testG.coins == G.coins);
	assert(testG.numActions == G.numActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.supplyCount[d] == testG.supplyCount[d]);

	printf("\n");

	// ----------- TEST 2: CHOICE 1: CURRENT CARD --------------
	printf("TEST 2 CHOICE 1 HAND POSITION INVALID NO CHANGE \n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice2 = 1;
	choice1 = handpos;
	d = G.hand[thisPlayer][choice1];
        cardEffectAmbassador(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.numActions == G.numActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.supplyCount[d] == testG.supplyCount[d]);

	printf("\n");

	// ----------- TEST 3: AMBASASADOR RUNS--------------
	printf("TEST 3: AMBASSADOR RUNS -1 card discarded\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][2] = curse;
	int cardsToBeDiscarded = 0;
	choice2 = 1;
	choice1 = 1;
	for (int m = 0; m < G.handCount[thisPlayer]; m++)
	{
		if (G.hand[thisPlayer][m] == choice1)
		{
			cardsToBeDiscarded++;
		}
	}

	int currentCardCount = 0;
	for (int m = 0; m < G.handCount[nextPlayer]; m++)
	{
		if (G.hand[nextPlayer][m] == choice1)
		{
			currentCardCount++;
		}
	}

	d = G.hand[thisPlayer][choice1];
	discarded = 1;
        cardEffectAmbassador(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.numActions == G.numActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded - choice2);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer] + 1);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.supplyCount[d] == testG.supplyCount[d] + choice2);
	int cardsDiscarded = 0;
	for (int m = 0; m < testG.handCount[thisPlayer]; m++)
	{
		if (testG.hand[thisPlayer][m] == choice1)
		{
			cardsDiscarded++;
		}
	}

	int cardCountAfter = 0;
	for (int m = 0; m < testG.handCount[nextPlayer]; m++)
	{
		if (testG.hand[nextPlayer][m] == choice1)
		{
			cardCountAfter++;
		}
	}

	assert(cardsDiscarded == (cardsToBeDiscarded - choice2));
	assert(cardCountAfter == currentCardCount + choice2);

	printf("\n");

	// ----------- TEST 4: AMBASASADOR RUNS--------------
	printf("TEST 4: AMBASSADOR RUNS -2 cards discarded\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][2] = curse;
	choice2 = 2;
	choice1 = 1;
	d = G.hand[thisPlayer][choice1];
	discarded = 1;
	cardsToBeDiscarded = 0;
	for (int m = 0; m < G.handCount[thisPlayer]; m++)
	{
		if (G.hand[thisPlayer][m] == choice1)
		{
			cardsToBeDiscarded++;
		}
	}

	currentCardCount = 0;
	for (int m = 0; m < G.handCount[nextPlayer]; m++)
	{
		if (G.hand[nextPlayer][m] == choice1)
		{
			currentCardCount++;
		}
	}
        cardEffectAmbassador(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.numActions == G.numActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded - choice2);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer] + choice2);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.supplyCount[d] == testG.supplyCount[d] + choice2);

	cardsDiscarded = 0;
	for (int m = 0; m < testG.handCount[thisPlayer]; m++)
	{
		if (testG.hand[thisPlayer][m] == choice1)
		{
			cardsDiscarded++;
		}
	}

	cardCountAfter = 0;
	for (int m = 0; m < testG.handCount[nextPlayer]; m++)
	{
		if (testG.hand[nextPlayer][m] == choice1)
		{
			cardCountAfter++;
		}
	}

	assert(cardsDiscarded == (cardsToBeDiscarded - choice2));
	assert(cardCountAfter == currentCardCount + choice2);


	// ----------- TEST 5: CHOICE 2 >number of cards--------------
	printf("TEST 5: CHOICE 2 > 2 NUMBER OF CARDS NO CHANGE \n");
	memcpy(&testG, &G, sizeof(struct gameState));
	for (int m = 0; m < G.handCount[thisPlayer]; m++)
	{
		if (G.hand[thisPlayer][m] == curse)
		{
			G.hand[thisPlayer][m] = baron;
		}
	}
	G.hand[thisPlayer][1] = curse;
	choice2 = 2;
        cardEffectAmbassador(choice1, choice2, &testG, handpos, thisPlayer);
	assert(testG.coins == G.coins);
	assert(testG.numActions == G.numActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.supplyCount[d] == testG.supplyCount[d]);

	printf("\n");

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);


	return 0;
}

