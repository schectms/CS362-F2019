#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

FILE *f;

#define TESTCARD "baron"

#define assert(x) {f=fopen("test1.txt", "a"); if (x == 0) fprintf(f, "Test Failed\n"); else fprintf(f, "Test Passed\n"); fclose(f);}

int main() {

	//seed random
	srand(time(NULL));

	//declare variables needed to call playBaron
	int i, j, l, choice1 = 0, currentPlayer = 0,
		seed = 0, numPlayers = 0;
	struct gameState G, testG;

	//initialize available cards for deck
	int k[10] = { baron, estate, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room };

	//open file for writing
	f=fopen("test1.txt", "w");
	fprintf(f, "BEGIN TESTING BARON\n");	
	fclose(f);
	//loop to test
	for (i = 0; i < 500; i++)
	{
		seed = 1000; //randomize seed
		numPlayers = (rand() % (4 + 1 - 2)) + 1; //randomize numPlayers
		choice1 = rand() % 2; //randomize choice1
		initializeGame(numPlayers, k, seed, &G); //start game
	
                currentPlayer = (rand() % numPlayers); //randomize current player
	
		//randomize the hand count for each player
		for (j = 0; j < numPlayers; j++)
		{
			G.handCount[j] = rand() % 10 + 1;
		}
		G.supplyCount[estate] = rand() % 10 + 1;
		
		//check how many estates are in the hand b4 test
		int estateFound = 0;
		for (l = 0; l < G.handCount[currentPlayer]; l++)
		{
			if (G.hand[currentPlayer][l] == estate)
			{
				estateFound ++;
				break;
			}
		}

		memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state for testing
		playBaron(&testG, choice1, currentPlayer); //call refactored function

		int a,b,c;
		//results for when an estate is discarded	 
		if (choice1 > 0 && estateFound == 1)
		{
			f=fopen("test1.txt", "a");
			fprintf(f, "Test # %d\n", i);
			fclose(f);

			assert(testG.numBuys==G.numBuys+1); //buys should be incremented
			assert(testG.coins==G.coins+4); //should have an additional 4 coins
			for(a=0;a<numPlayers;a++)
			{
				if(a!=currentPlayer)
				{
					//no chnages to other players
					assert(testG.handCount[a]==G.handCount[a]);  
					assert(testG.discardCount[a]==G.discardCount[a]);
				}
				else
				{
					assert(testG.handCount[a]==G.handCount[a]-2); //current player has 2 less cards
					assert(testG.discardCount[a]==G.discardCount[a]+1); //estate is now in discard pile

				}
			}
			assert(testG.supplyCount[estate]==G.supplyCount[estate]); //supply remins the same
                        assert(testG.playedCardCount==G.playedCardCount+1); //baron card in now in played cards
			
			//loops and checks number of estates after test ran
			int numEstates=0;
			for(b = 0; b < testG.handCount[currentPlayer]; b++)
			{
				numEstates++;
			}
			assert(numEstates==estateFound-1); //player should now have 1 less estate
		}

		//no estates available, no state change
		else if(G.supplyCount[estate] ==0)
		{
		        f=fopen("test1.txt", "a");
                        fprintf(f, "Test # %d\n", i);
                        fclose(f);
		
			assert(testG.handCount[currentPlayer]==G.handCount[currentPlayer]);
			assert(testG.coins==G.coins);
	
		}

		//tests that player gains estate properly
		else  
		{
			f=fopen("test1.txt", "a");
                        fprintf(f, "Test # %d\n", i);
                        fclose(f);

                        assert(testG.numBuys==G.numBuys+1); //buys shpuld be incremented
			assert(testG.coins==G.coins); //coin count stays the same
			for(a=0;a<numPlayers;a++)
                        {
                                assert(testG.handCount[a]==G.handCount); //no change to hand count for any palyers

				if(a!=currentPlayer)
				{
                                        assert(testG.discardCount[a]==G.discardCount[a]); //no estate discarded
				}
				else
				{
                                        assert(testG.discardCount[a]==G.discardCount[a]); //all other players state unchanged 
				}

                        }
			assert(testG.supplyCount[estate]==G.supplyCount[estate]-1);		//supply count decremented
			assert(testG.playedCardCount==G.playedCardCount+1); //baron card in playedCard
			
			int numEstates=0;
                        for(b = 0; b < testG.handCount[currentPlayer]; b++)
                        {
                                numEstates++;
                        }
                        assert(numEstates==estateFound+1); //player should now have 1 more estate

		}
	}
	return 0;
}

