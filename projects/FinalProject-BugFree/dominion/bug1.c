#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main(int argc, char** argv) {

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 1;
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;

	struct gameState G, testG; //declare game states

	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// ----------- TEST 1: BUG 1 TRIBUTE CARD NOT DISCARDED--------------
	printf("TEST 1: BUG 1 TRIBUTE CARD NOT DISCARDED\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	G.deck[nextPlayer][1] = mine;
	G.deck[nextPlayer][0] = copper;

	cardEffect(tribute, choice1, choice2, choice3, &testG, handPos, &bonus);
	//playedCards should contain the tribute card
	printf("Result of Card Effect= %d, Expected = %d\n", testG.playedCardCount, G.playedCardCount + 1);

	// ----------- TEST 2: BUG 1 MINE CARD NOT DISCARDED--------------
	printf("TEST 1: BUG 1 MINE CARD NOT DISCARDED\n");

	choice1 = 2;
	G.hand[thisPlayer][choice1] = copper;
	choice2 = steward;

	memcpy(&testG, &G, sizeof(struct gameState));
	int x=cardEffect(mine, choice1, choice2, choice3, &testG, handPos, &bonus);
	//trashed card should not be in playedCards
	printf("Result of Card Effect= %d, Expected = %d\n", testG.playedCardCount, G.playedCardCount +1);

	return 0;
}

