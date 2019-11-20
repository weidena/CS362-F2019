#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void main (int argc, char** argv)	
{
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    printf("Begin Testing callMine():\n");

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, atoi(argv[1]), &G);
    int who = G.whoseTurn;
    gainCard(mine, &G, 0, who);
    callMine(0, 1, &G, 0, who);

    

}