#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"


int main () {

	//set default cards
    int k[11] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall, tribute
                };

	//declare game state
    struct gameState G;	

    printf ("Testing Game Initialization-More Than 2 Players");
	
	//allocate memory for game and initialize
	memset(&G, 23, sizeof(struct gameState)); 
	initializeGame(4, k, 11, &G); 	
	
	printf("%d/n", G.numPlayers);

	return 0;
}
