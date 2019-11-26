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
    int k[10] = {adventurer, embargo, village, minion, cutpurse, sea_hag, tribute, smithy, council_room};
    int card = feast;
    int choice1 = province;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int bonus = 0;
    int i;
    int foundCard = 0;

    //initialize a new game
    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));

    //use a known valid choice
    choice1 = silver;

    printf("TEST 1: check if player gained coins.\n");

    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);

    
    printf("Expected number of coins: %d, Actual number of coins: %d\n", G.coins, testG.coins);

    if(G.coins == testG.coins)
    {
        printf("Test passed for not adding coins to player.\n");
    }

    else
    {
        printf("Test failed for adding coins to player.\n");
    }

    printf("TEST 1 has completed.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    //test if valid card chosen was given to player
    printf("TEST 2: check if player gained valid card.\n");

    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);

    for(i = 0; i < testG.discardCount[currentPlayer]; i++)
    {
        if(testG.discard[currentPlayer][i] == choice1)
        {
            foundCard = 1;
        }
        
    }

    //if player gained card then passed otherwise failed
    if(foundCard == 1)
    {
        printf("Test passed for gaining card selected by player.\n");
    }

    else
    {
        printf("Test failed for not gaining card selected by player.\n");
    }
    
    
    return 0;
}