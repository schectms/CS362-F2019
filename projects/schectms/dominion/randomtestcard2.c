#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

FILE* f;

#define TESTCARD "minion"

#define assert(x) {f=fopen("test2.txt", "a"); if (x == 0) fprintf(f, "Test Failed\n"); else fprintf(f, "Test Passed\n"); fclose(f);}

int main() {

	//seed random
	srand(time(NULL));

	//declare variables needed to call playBaron
	int i, j, choice1 = 0, choice2 = 0, currentPlayer = 0,
		seed = 0, numPlayers = 0, handpos = 0;
	struct gameState G, testG;

	//initialize available cards for deck
	int k[10] = { baron, estate, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	//start loop for testing
	f = fopen("test2.txt", "w");
	fprintf(f, "BEGIN TESTING MINION\n");
	fclose(f);

	for (i = 0; i < 500; i++)
	{
		f = fopen("test2.txt", "a");
		fprintf(f, "Test # %d\n", i);
		fclose(f);
		
		seed = 1000; //randomize seed
		
		numPlayers = (rand() % (4 + 1 - 2)) + 1; //randomize numPlayers
		//currentPlayer = (rand() % numPlayers); //randomize current player

		if ((rand() % 1) == 0)
		{
			choice1 = 0;
			choice2 = 1;
		}

		else
		{
			choice1 = 1;
			choice2 = 0;
		}

		initializeGame(numPlayers, k, seed, &G); //start game
		//randomize the hand count for each player
		for (j = 0; j < numPlayers; j++)
		{
			G.handCount[j] = rand() % 10 + 1;
		}
		memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state for testing
		playMinion(&testG, handpos, currentPlayer, choice1, choice2); //call refactored function
		//gains coins
		if (choice1 == 1)
		{
			assert((testG.coins) == (G.coins + 2)); //player needs to gain 2 coins
			assert(testG.numActions == G.numActions + 1); //actions needs to be incremented
			int a;
			for (a = 0; a < numPlayers; a++)
			{
				if (a == currentPlayer)
				{
					assert(testG.handCount == (G.handCount - 1)); //same hand-minion card
					assert(testG.discardCount[a] == G.discardCount[a]); //no cards discarded
				}
				else
				{
					assert(testG.handCount[a] == G.handCount[a]); //all other players hands have not chnaged
					assert(testG.discardCount[a] == G.discardCount[a]); //no cards discarded

				}
			}
			assert(testG.playedCardCount == G.playedCardCount + 1); //minion card played
		}
		else if (choice2 == 1)
		{
			assert(testG.coins == G.coins); //coins do not change
			assert(testG.numActions == (G.numActions + 1)); //actions needs to be incremented
			int b;
			for (b = 0; b < numPlayers; b++)
			{
				if (G.handCount[b] > 5 || b == currentPlayer)
				{
					assert(testG.handCount[b] == 4); //all players with >5 cards discard and get 4 new ones
				}
				else
				{
					assert(testG.handCount[b] == G.handCount[b]); //all other players card count stays the same

				}
			}
			assert(testG.playedCardCount == G.playedCardCount + 1); //minion card played

		}
	}
	return 0;
}

