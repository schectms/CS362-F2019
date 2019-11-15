#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

FILE *f;

#define TESTCARD "tribute"

#define assert(x) {f=fopen("test3.txt", "a"); if (x == 0) fprintf(f, "Test Failed\n"); else fprintf(f, "Test Passed\n"); fclose(f);}

int main() {

	//seed random
	srand(time(NULL));

	//declare variables needed to call playBaron
	int i, j, seed, numPlayers, currentplayer = 0, nextplayer = 1;
	struct gameState G, testG;

	//initialize available cards for deck
	int k[10] = { baron, estate, village, minion, mine, cutpurse,
									sea_hag, tribute, smithy, council_room };
	f=fopen("test3.txt", "w");
	fprintf(f, "BEGIN TESTING TRIBUTE\n");
	fclose(f);
	//start loop for testing
	for (i = 0; i < 500; i++)
	{

		f=fopen("test3.txt", "a");
                fprintf(f, "Test # %d\n", i);
                fclose(f);

		seed = 1000; //randomize seed
		numPlayers = (rand() % (4 + 1 - 2)) + 1; //randomize numPlayers
		initializeGame(numPlayers, k, seed, &G); //start game
		//randomize the hand count for each player
		for (j = 0; j < numPlayers; j++)
		{
			G.handCount[j] = rand() % 10 + 1;
		}
		currentplayer = (rand() % numPlayers); //randomize current player
		//set nextplayer based on current
		if(currentplayer !=numPlayers)
		{
			nextplayer=currentplayer+1;
		}
		else
		{
			nextplayer=0;
		}
		
		G.discardCount[nextplayer]= rand() % 20;
		G.deckCount[nextplayer]=rand() % 20;
	
		memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state for testing
		playTribute(&testG, nextplayer, currentplayer); //call refactored function
		
		int cards[2]={-1, -1};
		if(G.deckCount[nextplayer] >=2)
		{
			cards[0]=G.deck[nextplayer][0];
			cards[1]=G.deck[nextplayer][1];
		}
		else if(G.deckCount[nextplayer]==1) 
		{
			cards[0]=G.deck[nextplayer][0];
			if(G.discardCount[nextplayer]>=1)
			{
				cards[1]=G.discard[nextplayer][0];
			}
		}
		else
		{
			if(G.discardCount[nextplayer]>=2)
			{
				cards[0]=G.discard[nextplayer][0];
				cards[1]=G.discard[nextplayer][1];
			}
			else if(G.discardCount[nextplayer]==1)
			{				
				cards[0]=G.discard[nextplayer][0];
			}
		}
	
		if(cards[0]==cards[1])
		{
			cards[1]=-1;
		}	
		int b;
		for(b=0;b<2;b++)
		{
			if (cards[b]==copper || cards[b]==silver || cards[b]==gold)
			{
				assert(testG.coins==G.coins +2);	
			}
			else if(cards[b]==estate || cards[b]==duchy ||cards[b]==province
			|| cards[b]==gardens || cards[b]==great_hall)
			{
			
				assert(testG.handCount[currentplayer]==G.handCount[currentplayer]+2);
			}
			else
			{
		
				assert(testG.numActions==G.numActions +2);
			}
		}
		
		
	}
	return 0;
}

