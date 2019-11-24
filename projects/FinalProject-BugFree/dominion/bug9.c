/*
 * Author: Kristin Wood
 * Description: Unit test for bug 9
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
    int o = 1;

    //Declare arrays of cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    //Initialize game
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    //Call with 2 of the same treasure card
    G.deck[o][0] = silver;
    G.deck[o][1] = silver;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    G.whoseTurn = 0;
    int actions = G.numActions;
    int coins = G.coins;
    int cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("Calling cardEffect for Tribute with 2 silver cards\n");
    cardEffect(tribute, -1, -1, -1, &G, 0, NULL);
    int result = assert(G.coins == coins+2);
    if (!result) {
        printf("FAIL - Coins did not increase by 2.\n");
    }
    else {
        printf("PASS - Coins increased by 2.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }

    //Call with 2 of the same victory
    G.deck[o][0] = estate;
    G.deck[o][1] = estate;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffect for Tribute with 2 estate cards\n");
    cardEffect(tribute, -1, -1, -1, &G, 0, NULL);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p] + 2);
    if (!result) {
        printf("FAIL - Number of cards did not increase by 2.\n");
    }
    else {
        printf("PASS - Number of cards increased by 2.\n");
    }

    //Call with 2 of the same action
    G.deck[o][0] = baron;
    G.deck[o][1] = baron;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffect for Tribute with 2 baron cards\n");
    cardEffect(tribute, -1, -1, -1, &G, 0, NULL);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions+2);
    if (!result) {
        printf("FAIL - Number of actions did not increase by 2.\n");
    }
    else {
        printf("PASS - Number of actions increased by 2.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }
}
