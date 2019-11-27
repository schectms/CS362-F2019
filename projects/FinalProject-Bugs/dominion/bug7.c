#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{

    //set up game state
    struct gameState G, testG;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int card = tribute;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int bonus = 0;
    int currentPlayer = 0;
    int nextPlayer = currentPlayer + 1;
    int expectedHandCards = 0;
    int actualHandCards = 0;
    int expectedNumActions = 0;
    int actualNumActions = 0;

    //initialize a new game
    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));

    testG.deck[nextPlayer][0] = silver;
    testG.deck[nextPlayer][1] = mine;

    //test if coinss are added correctly or if counted more than once
    printf("TEST 1: testing with first revealed card to be a treasure card if coins added to player are more than expected.\n");

    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);

    printf("Expected number of coins: %d, Actual number of coins: %d\n", G.coins + 2, testG.coins);

    if(testG.coins != (G.coins + 2))
    {
        printf("Test failed for not awarding player correct number of coins for one treasure card.\n");
    }

    else
    {
        printf("Test passed for awarding player correct number of coins for one treasure card.\n");
    }

    printf("TEST 1 has completed.\n");
    
    //test if correct cards added to hand for one victory card
    printf("TEST 2: testing with first revealed card to be victory card if number of cards added to player is more than expected.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    //set nextPlayer deck to have 1 of the top 2 cards to be a victory card
    testG.deck[nextPlayer][0] = estate;
    testG.deck[nextPlayer][1] = mine;

    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);

    //set variables for expected and actual cards in hand
    expectedHandCards = G.handCount[currentPlayer] + 2;
    actualHandCards = testG.handCount[currentPlayer];

    printf("Expected number of cards in player's hand: %d, Actual number of cards in player's hand: %d\n", expectedHandCards, actualHandCards);

    if(expectedHandCards == actualHandCards)
    {
        printf("Test passed for adding correct number of cards to player's hand.\n");
    }

    else
    {
        printf("Test failed for not adding correct number of cards ot player's hand.\n");
    }

    printf("TEST 2 has completed.\n");

    //test with one action card if player received correct num actions
    printf("TEST 3: testing with first revealed card to be action card if number of actions is more than expected.\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deck[nextPlayer][0] = baron;
    testG.deck[nextPlayer][1] = estate;

    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);
    
    //set variable for expected and actual number of actions
    expectedNumActions = G.numActions + 2;
    actualNumActions = testG.numActions;

    printf("Expected number of actions: %d, Actual number of actions: %d\n", expectedNumActions, actualNumActions);

    if(expectedNumActions == actualNumActions)
    {
        printf("Test passed for awarding player correct number of actions for one action card.\n");
    }

    else
    {
        printf("Test failed for not awarding player correct numbero of actions for one action card.\n");
    }

    return 0;
}