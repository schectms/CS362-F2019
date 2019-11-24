/*
 * Author: Kristin Wood
 * Description: Unit test for bug 8
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

int assert(int expression) {
    if (expression) {
        //true
        return 1;
    }
    else {
        //false
        return 0;
    }
}

int main (int argc, char** argv) {
    //Set up game state
    struct gameState G;
    int seed = time(NULL);
    int numPlayers = 2;
    int p = 0;

    //Declare arrays of cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    //Initialize game
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    //Play playCard with a card that assigns bonus to coins directly. Check coins after and it will have been overwritten.
    G.hand[p][0] = baron;
    G.hand[p][1] = estate;
    G.handCount[p] = 2;
    G.whoseTurn = 0;
    updateCoins(G.whoseTurn, &G, 0);

    printf("Playing Baron card and discarding estate through playCard function\n");
    playCard(0, 1, -1, -1, &G);

   int result = assert(G.coins == 4);
   if (!result) {
       printf("FAIL - Did not receive correct bonus.\n");
   }
   else {
       printf("PASS - Received correct bonus.\n");
   }
}
