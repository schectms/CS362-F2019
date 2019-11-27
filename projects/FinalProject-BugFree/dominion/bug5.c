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
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int i, j, l;
    int score = 0;
    int expectedDeckScore = 0;
    int actualDeckScore = 0;

    //initialize a new game
    initializeGame(numPlayers, k, seed, &G);

    printf("TEST 1: check score for deck when discardCont is lower than deckCount.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    //set discardCount and deckCount for player
    testG.discardCount[currentPlayer] = 7;
    testG.deckCount[currentPlayer] = 10;

    //set known cards for hand, discard and deck
    for(i = 0; i < numHandCards(&testG); i++)
    {
        testG.hand[currentPlayer][i] = estate;
    }

    for(j = 0; j < testG.discardCount[currentPlayer]; j++)
    {
        testG.discard[currentPlayer][j] = great_hall;
    }

    for(l = 0; l < testG.deckCount[currentPlayer]; l++)
    {
        testG.deck[currentPlayer][l] = duchy;
    }

    score = scoreFor(currentPlayer, &testG);

    //set acutal and expected deck scores
    actualDeckScore = score - 12;
    expectedDeckScore = 30;

    //compare expected to actual deck score
    printf("Expected Deck score: %d, Actual Deck Score: %d\n", expectedDeckScore, actualDeckScore);

    //test if passed
    if(expectedDeckScore == actualDeckScore)
    {
        printf("Test passed for calculating the correct score.\n");
    }

    else
    {
        printf("Test failed for not calculating the correct score.\n");
    }

    printf("TEST 1 has completed.\n");

    printf("TEST 2: check score for deck when discardCount is more than deckCount.\n");

    expectedDeckScore = 0;
    actualDeckScore = 0;
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.discardCount[currentPlayer] = 10;
    testG.deckCount[currentPlayer] = 7;

    for(i = 0; i < numHandCards(&testG); i++)
    {
        testG.hand[currentPlayer][i] = estate;
    }

    for(j = 0; j < testG.discardCount[currentPlayer]; j++)
    {
        testG.discard[currentPlayer][j] = great_hall;
    }

    for(l = 0; l < testG.deckCount[currentPlayer]; l++)
    {
        testG.deck[currentPlayer][l] = duchy;
    }

    score = scoreFor(currentPlayer, &testG);
    expectedDeckScore = 21;
    actualDeckScore = score - 15;

    printf("Expected Deck Score: %d, Actual Deck Score: %d\n", expectedDeckScore, actualDeckScore);

    if(expectedDeckScore == actualDeckScore)
    {
        printf("Test passed for calculating correct score.\n");
    }

    else
    {
        printf("Test failed for not calculating correct score.\n");
    }

    printf("TEST 2 has completed.\n");

    return 0;
    
}