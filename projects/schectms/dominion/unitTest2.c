#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

int x;
#define assert(x) {if (x == 0) printf("Test Failed\n"); else printf("Test Passed\n");}

int main() {
	int newCards = 0;
	int discarded = 1;
	int xtraCoins = 0;
	int shuffledCards = 0;
	int extraActions = 0;

	int i, j, m;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int remove1, remove2;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 1;
	struct gameState G, testG;

	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 CHOICE 1: 1 GAIN 2 COINS --------------
	printf("TEST 1 CHOICE 1: 1 GAIN 2 COINS\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;
	newCards = 0;
	xtraCoins = 2;
	extraActions = 1;

	playMinion(&testG, handpos, thisPlayer, choice1, choice2);

	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + extraActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
	assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	assert(testG.coins == G.coins + xtraCoins);

	printf("\n");

	// ----------- TEST 2 CHOICE 2: 1 REDRAW--------------
	printf("TEST 2 CHOICE 2: 1 REDRAW\n");
	// copy the game state to a test case
	G.handCount[nextPlayer] = 5;

	G.hand[nextPlayer][0] = steward;
	G.hand[nextPlayer][1] = copper;
	G.hand[nextPlayer][2] = duchy;
	G.hand[nextPlayer][3] = estate;
	G.hand[nextPlayer][4] = feast;

	int r1 = G.hand[nextPlayer][0];
	int r2 = G.hand[nextPlayer][1];
	int r3 = G.hand[nextPlayer][2];
	int r4 = G.hand[nextPlayer][3];
	int r5 = G.hand[nextPlayer][4];

	G.handCount[thisPlayer] = 4;

	G.hand[thisPlayer][0] = steward;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = estate;

	int r6 = G.hand[thisPlayer][0];
	int r7 = G.hand[thisPlayer][1];
	int r8 = G.hand[thisPlayer][2];
	int r9 = G.hand[thisPlayer][3];


	choice1 = 0;
	choice2 = 1;
	newCards = 4;
	extraActions = 1;
	int hc = G.handCount[thisPlayer];
	int hc1 = G.handCount[nextPlayer];

	memcpy(&testG, &G, sizeof(struct gameState));

	playMinion(&testG, handpos, thisPlayer, choice1, choice2);

	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + extraActions);
	assert(testG.handCount[thisPlayer] == 4);
	assert(testG.handCount[nextPlayer] == 4);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + hc + discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + hc + discarded);
	printf("\n");


	for (int m = 0; m < testG.handCount[nextPlayer]; m++) {
		assert((testG.hand[nextPlayer][m] != r1) && (testG.hand[nextPlayer][m] != r2)
			&& (testG.hand[nextPlayer][m] != r3) && (testG.hand[nextPlayer][m] != r4) && (testG.hand[nextPlayer][m] != r5));
	}

	for (int m = 0; m < testG.handCount[thisPlayer]; m++) {
		assert((testG.hand[thisPlayer][m] != r6) && (testG.hand[thisPlayer][m] != r7)
			&& (testG.hand[thisPlayer][m] != r8) && (testG.hand[thisPlayer][m] != r9));
	}

	// ----------- TEST 3 CHOICE 2: 1 REDRAW--------------
	printf("TEST 3 CHOICE 2: 1 REDRAW- next player does not\n");
	// copy the game state to a test case
	G.handCount[nextPlayer] = 3;

	G.hand[nextPlayer][0] = steward;
	G.hand[nextPlayer][1] = copper;
	G.hand[nextPlayer][2] = duchy;


	r1 = G.hand[nextPlayer][0];
	r2 = G.hand[nextPlayer][1];
	r3 = G.hand[nextPlayer][2];
	r4 = G.hand[nextPlayer][3];
	r5 = G.hand[nextPlayer][4];

	G.handCount[thisPlayer] = 4;

	G.hand[thisPlayer][0] = steward;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = duchy;
	G.hand[thisPlayer][3] = estate;

	r6 = G.hand[thisPlayer][0];
	r7 = G.hand[thisPlayer][1];
	r8 = G.hand[thisPlayer][2];
	r9 = G.hand[thisPlayer][3];

	choice1 = 0;
	choice2 = 1;
	newCards = 4;
	extraActions = 1;
	hc = G.handCount[thisPlayer];
	hc1 = G.handCount[nextPlayer];

	memcpy(&testG, &G, sizeof(struct gameState));

	playMinion(&testG, handpos, thisPlayer, choice1, choice2);

	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + extraActions);
	assert(testG.handCount[thisPlayer] == 4);
	assert(testG.handCount[nextPlayer] == testG.handCount[nextPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + hc + discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);

	for (int m = 0; m < testG.handCount[thisPlayer]; m++) {
		assert((testG.hand[thisPlayer][m] != r6) && (testG.hand[thisPlayer][m] != r7)
			&& (testG.hand[thisPlayer][m] != r8) && (testG.hand[thisPlayer][m] != r9));
	}

	assert(testG.hand[nextPlayer][0] == G.hand[nextPlayer][0]);
	assert(testG.hand[nextPlayer][1] == G.hand[nextPlayer][1]);
	assert(testG.hand[nextPlayer][2] == G.hand[nextPlayer][2]);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
