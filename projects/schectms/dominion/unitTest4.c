#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

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
	struct gameState G, testG; // set up structure for the game and the test
	//initialize available cards for deck
	int k[10] = { baron, estate, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = invalid error--------------

	printf("TEST 1: choice1 = invalid = error\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = mine;
	choice1 = 1;
	choice2 = steward;
	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

	// ----------- TEST 2: choice2 = invalid error--------------
	printf("TEST 2: choice2 = invalid = error\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = -1;
	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

	// ----------- TEST 3: choice2 = too expensive--------------
	printf("TEST 3: choice2 = too expensive = error\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = adventurer;
	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

	// ----------- TEST 4: choice 1 and choice 2 ok!--------------
	printf("TEST 4: mine code runs\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	G.hand[thisPlayer][1] = copper;
	choice1 = 1;
	choice2 = steward;
	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
