/*
 * Author: Kristin Wood
 * Description: Unit test for bug 10
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

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

    G.hand[p][0] = ambassador;
    G.hand[p][1] = copper;
    G.hand[p][2] = estate;
    G.hand[p][3] = tribute;
    G.hand[p][4] = estate;
    G.handCount[p] = 5;
    G.whoseTurn = 0;
    printf("Calling cardEffect for Ambassador with choice to discard a Tribute card\n");
    int result = cardEffect(ambassador, 3, 1, NULL, &G, 0, NULL);
    result = assert(result == 0);
    if (!result) {
        printf("FAIL - Function exited with wrong exit code.\n");
    }
    else {
        printf("PASS - Function exited with correct exit code.\n");
    }
    int numTributes = 0;
    for (int i = 0; i < G.handCount[p]; i++) {
        if (G.hand[p][i] == tribute) {
            numTributes++;
        }
    }
    result = assert(numTributes == 0);
    if (!result) {
        printf("FAIL - Player still has Tribute card.\n");
    }
    else {
        printf("PASS - Player no longer has Tribute card.\n");
    }

    G.hand[p][0] = ambassador;
    G.hand[p][1] = copper;
    G.hand[p][2] = estate;
    G.hand[p][3] = minion;
    G.hand[p][4] = minion;
    G.handCount[p] = 5;
    printf("Calling cardEffect for Ambassador with choice to discard two Minion cards\n");
    int result = cardEffect(ambassador, 3, 2, NULL, &G, 0, NULL);
    result = assert(result == 0);
    if (!result) {
        printf("FAIL - Function exited with wrong exit code.\n");
    }
    else {
        printf("PASS - Function exited with correct exit code.\n");
    }
    int numMinions = 0;
    for (int i = 0; i < G.handCount[p]; i++) {
        if (G.hand[p][i] == minion) {
            numMinions++;
        }
    }
    result = assert(numMinions == 0);
    if (!result) {
        printf("FAIL - Player still has Minion card.\n");
    }
    else {
        printf("PASS - Player no longer has Minion cards.\n");
    }
}
