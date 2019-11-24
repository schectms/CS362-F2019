/*
 * Author: Kristin Wood
 * Description: Unit test for bug 4
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

    //Declare arrays of cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    //Initialize game
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.supplyCount[0] = 0;
    G.supplyCount[26] = 0;
    G.supplyCount[27] = 0;

    printf("Calling isGameOver with 0 cards at indices 0, 26 and 27\n");

    int result = isGameOver(&G);
    result = assert(result == 1);
    if (!result) {
        printf("FAIL - isGameOver did not return 1.\n");
    }
    else {
        printf("PASS - isGameOver returned 1.\n");
    }

    //Initialize game
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;
    G.supplyCount[27] = 0;

    printf("Calling isGameOver with 0 cards at indices 0, 1 and 27\n");

    result = isGameOver(&G);
    result = assert(result == 1);
    if (!result) {
        printf("FAIL - isGameOver did not return 1.\n");
    }
    else {
        printf("PASS - isGameOver returned 1.\n");
    }
}
