#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main(int argc, char** argv) {

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 1;
	int choice1 = 1, choice2 = 0, choice3 = 0, handPos = 3, bonus = 0;

	struct gameState G, testG; //declare game states

	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// ----------- TEST 1: Remodel returns error when player tries to make valid purchase      --------------
	printf("TEST 1: Remodel returns error when player tries to make valid purchase\n");


	memcpy(&testG, &G, sizeof(struct gameState));
	testG.hand[thisPlayer][1] = ambassador;
	choice2 = cutpurse;
	testG.supplyCount[cutpurse] = 3;
	int x = cardEffect(remodel, choice1, choice2, choice3, &testG, handPos, &bonus);

	printf("Result of Card Effect= %d, Expected = %d\n", x, 0);
	printf("Top Card= %d, Expected = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], cutpurse);
	printf("\n");

	// ----------- TEST : Remodel runs when player tries to make invalid purchase      --------------
	printf("TEST 2: Remodel runs when player tries to make invalid purchase\n");


	memcpy(&testG, &G, sizeof(struct gameState));
	testG.hand[thisPlayer][1] = embargo;
	choice2 = adventurer;
	x = cardEffect(remodel, choice1, choice2, choice3, &testG, handPos, &bonus);

	printf("Result of Card Effect= %d, Expected = %d\n", x, -1);
	//	printf("Top Card= %d, Expected = %d\n", testG.hand[thisPlayer][0], G.hand[thisPlayer][0]);
	printf("\n");

	return 0;
}



