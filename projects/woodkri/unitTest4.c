#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

#define assert(x) {if (x == 0) printf("Test Failed\n"); else printf("Test Passed\n");}

int main() {

	//initialize variables for testing
	int discarded = 1;
	int xtraCoins = 0;
	int extraBuys = 1;
	int estateGained = 0;

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

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 CHOICE 1: NOT A COIN NO CHANGE--------------

	printf("TEST 1 CHOICE 1: NOT A COIN NO CHANGE\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = mine;
	choice1 = 1;
	choice2 = steward;
        cardEffectMine(choice1, choice2, &testG, handpos, thisPlayer);


	assert(testG.coins == G.coins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);

	printf("\n");

	// ----------- TEST 2 CHOICE 2: INVALID NO CHANGE-------------
	printf("TEST 2 CHOICE 2: INVALID NO CHANGE\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = -1;
        cardEffectMine(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);

	printf("\n");

	// ----------- TEST 3 CHOICE 2: TOO EXPENSIVE NO CHANGE--------------
	printf("TEST 3 CHOICE 2: TOO EXPENSIVE NO CHANGE\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = adventurer;
        cardEffectMine(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);

	printf("\n");

	// ----------- TEST 4: choice 1 and choice 2 ok!--------------
	printf("TEST 4: MINE RUNS\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = steward;
	int d = G.hand[thisPlayer][choice1];

	int num = 0;
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		if (G.hand[thisPlayer][i] == steward)
		{
			num++;
		}
	}

        cardEffectMine(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - 2);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.supplyCount[choice2] == G.supplyCount[choice2] - 1);



	int num2 = 0;
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == steward)
		{
			num2++;
		}
	}

	assert(num2==num+1);
	assert(G.hand[thisPlayer][choice1] != choice2);
	printf("\n");

	// ----------- TEST 5--------------
	printf("BUG 2- Tries to discard too expensive card \n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = council_room;

        cardEffectMine(choice1, choice2, &testG, handpos, thisPlayer);

	assert(testG.coins == G.coins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
