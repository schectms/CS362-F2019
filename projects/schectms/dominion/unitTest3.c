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
	int discarded = 1;
	int xtraCoins = 0;
	int extraBuys = 1;
	int estateGained = 0;

	int i; //looping variable
	//initialize parameters for cardEffect
	int handpos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG; // set up structure for the game and the test
	//initialize available cards for deck
	int k[10] = { baron, estate, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	memcpy(&testG, &G, sizeof(struct gameState));
	choice2 = 3;
	cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);

	memcpy(&testG, &G, sizeof(struct gameState));
	choice2 = 1;
	choice1 = handpos;
	cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);

	memcpy(&testG, &G, sizeof(struct gameState));
	choice2 = 1;
	G.hand[thisPlayer][1] = curse;
	choice1 = 1;
	cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);


	return 0;
}
