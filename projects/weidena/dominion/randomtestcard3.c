#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void assertTrue(int test, int value) {
	if (test == value) {
		printf("PASSED\t");
	}
	else {
		printf("FAILED\t");
	}
}

int testTribute(int handPos, int revealedCard1, int revealedCard2, int currentPlayer, struct gameState *state) {

    // initialie gameState
	struct gameState gTest;
	memcpy(&gTest, state, sizeof(struct gameState));

    // call callTribute
	int val = callTribute(revealedCard1, revealedCard2, state, handPos, currentPlayer, currentPlayer-1);

    // test option of treasure
    if (revealedCard1 == copper || revealedCard1 == silver || revealedCard1 == gold) {
        printf("CASE: treasure added\n");

        assertTrue(gTest.coins + 2, state->coins);
        printf("TEST: +2 coins\n");

        assertTrue(gTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
        printf("TEST: deck unchanged.\n");

        assertTrue(gTest.handCount[currentPlayer], state->handCount[currentPlayer]);
        printf("TEST: hand unchanged.\n");
        
        assertTrue(gTest.numActions, state->numActions);
        printf("TEST: actions unchanged.\n");
    }

    // test optionof victory card
    else if (revealedCard1 == estate || revealedCard1 == duchy || revealedCard1 == province || revealedCard1 == gardens || revealedCard1 == great_hall) {
        printf("CASE: victory added\n");
        
        assertTrue(gTest.handCount[currentPlayer] + 2, state->handCount[currentPlayer]);
        printf("TEST: +2 cards.\n");

        assertTrue(gTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
        printf("TEST: deck unchanged.\n");

        assertTrue(gTest.coins, state->coins);
        printf("TEST: coins unchanged.\n");

        assertTrue(gTest.numActions, state->numActions);
        printf("TEST: actions unchanged.\n");
    }

    // test option of action card
    else {
        printf("CASE: action added\n");
        
        assertTrue(gTest.numActions + 2, state->numActions);
        printf("TEST: +2 actions.\n");
        
        assertTrue(gTest.deckCount[currentPlayer], state->deckCount[currentPlayer]);
        printf("TEST: deck unchanged.\n");
        
        assertTrue(gTest.coins, state->coins);
        printf("TEST: coins unchanged.\n");
        

    }
	return val;
}

int main() {

	struct gameState G;
	srand(time(0));

	printf("\nTESTS FOR TRIBUTE\n");
	for (int i = 0; i < 2000; i++) {
		for (int j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		int numPlayers = rand() % 2 + 3;
		G.numPlayers = numPlayers;

        // initialize hand
		for (int k = numPlayers; k >= numPlayers - 1; k--) {
			G.handCount[k] = 0;
			for (int j = 0; j < 20; j++) {
				int card = rand() % 20 + 1;
				gainCard(card, &G, 1, k);
				G.deckCount[k] = j + 1;
			}
			G.handCount[k] = 0;
			for (int j = 0; j < 5; j++) {
				drawCard(k, &G);
				G.handCount[k] = j + 1;
			}
		}
		if(rand() % 5 == 0){
			G.handCount[numPlayers - 1] = 2;
			G.deckCount[numPlayers - 1] = rand() % 2;
			G.discardCount[numPlayers - 1] = rand() % 2;
		}
		int random = rand() % 3;
		int revealedCard1 = G.hand[numPlayers - 1][0];
		int revealedCard2 = G.hand[numPlayers - 1][1];
		if (random == 0) {
			revealedCard1 = revealedCard2;
		}

		testTribute(0, revealedCard1, revealedCard2, numPlayers, &G);
	}

	return 0;
}