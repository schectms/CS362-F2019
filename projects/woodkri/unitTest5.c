#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "tribute"

#define assert(x) {if (x == 0) printf("Test Failed\n"); else printf("Test Passed\n");}

int main() {

	//initialize variables for testing
	int discarded = 1;
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

	int tributeRevealedCards[2] = {-1, -1};
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 CHOICE 1: NOT A COIN NO CHANGE--------------
	
	printf("TEST 1\n");
	G.discard[nextPlayer][0] = copper;
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffectTribute(&testG, thisPlayer, nextPlayer, tributeRevealedCards);
	//player gains 2 coins, discards tribute card, nextplayer discards 1 card
	int xtraCoins = 2;
	int xtraActions = 0;
	int xtraCards = 0;
	int discardnp = 1;
	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + xtraActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] +xtraCards-discarded);
	assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer]);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]-1);
	printf("\n");


	printf("TEST 2\n");
	G.deck[nextPlayer][0] = estate;
	G.deckCount[nextPlayer] = 1;
	G.discardCount[nextPlayer] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	 cardEffectTribute(&testG, thisPlayer, nextPlayer, tributeRevealedCards);
	//player gains 2 cards, discards tribute card, nextplayer discards 1 card
	xtraCoins = 0;
	xtraActions = 0;
	xtraCards = 2;
	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + xtraActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + xtraCards - discarded);
	assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer]-1);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	printf("\n");

	printf("TEST 3\n");
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
        cardEffectTribute(&testG, thisPlayer, nextPlayer, tributeRevealedCards);

	//nothing happens
	xtraCoins = 0;
	xtraActions = 0;
	xtraCards = 0;
	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + xtraActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + xtraCards - discarded);
	printf("\n");

	printf("TEST 4\n");
	G.discard[nextPlayer][1] = mine;
	G.discard[nextPlayer][0] = mine;
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 2;
	memcpy(&testG, &G, sizeof(struct gameState));
        cardEffectTribute(&testG, thisPlayer, nextPlayer, tributeRevealedCards);

	//player gains 2 actions, discards tribute card, nextplayer discards 2 cards
	xtraCoins = 0;
	xtraActions = 2;
	xtraCards = 0;
	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + xtraActions);
        printf("Expected Actions: %d Actual Actions: %d\n", (testG.numActions +2), G.numActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + xtraCards - discarded);
	assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]-2);
	printf("\n");


	printf("TEST 5\n");
	G.deck[nextPlayer][1] = mine;
	G.deck[nextPlayer][0] = copper;
	G.deckCount[nextPlayer] = 2;
	G.discardCount[nextPlayer] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
        cardEffectTribute(&testG, thisPlayer, nextPlayer, tributeRevealedCards);

	//player gains 2 actions, 2 coins, discards tribute card, nextplayer discards 2 card
	xtraCoins = 0;
	xtraActions = 2;
	xtraCards = 2;
	assert(testG.coins == G.coins + xtraCoins);
	assert(testG.numActions == G.numActions + xtraActions);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + xtraCards - discarded);
	printf("\n");

	


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
