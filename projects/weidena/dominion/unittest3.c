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

    // initialie game
	int numCards = state->handCount[currentPlayer];
	int numActions = state->numActions;
	int money = state->coins;
	int fullDeck = state->deckCount[currentPlayer];
	int opponentDeckCount = state->deckCount[1];
	int opponentHandCount = state->handCount[1];
    
    // call callTribute
	int val = callTribute(revealedCard1, revealedCard2, state, handPos, currentPlayer, currentPlayer-1);

    // test option of treasure
    if (revealedCard1 == copper || revealedCard1 == silver || revealedCard1 == gold) {
        printf("CASE: treasure added\n");

        assertTrue(money + 2, state->coins);
        printf("TEST: +2 coins\n");

        assertTrue(fullDeck, state->deckCount[currentPlayer]);
        printf("TEST: deck unchanged.\n");

        assertTrue(numCards, state->handCount[currentPlayer]);
        printf("TEST: hand unchanged.\n");
        
        assertTrue(numActions, state->numActions);
        printf("TEST: actions unchanged.\n");
    }

    // test optionof victory card
    else if (revealedCard1 == estate || revealedCard1 == duchy || revealedCard1 == province || revealedCard1 == gardens || revealedCard1 == great_hall) {
        printf("CASE: victory added\n");
        
        assertTrue(numCards + 2, state->handCount[currentPlayer]);
        printf("TEST: +2 cards.\n");

        assertTrue(fullDeck, state->deckCount[currentPlayer]);
        printf("TEST: deck unchanged.\n");

        assertTrue(money, state->coins);
        printf("TEST: coins unchanged.\n");

        assertTrue(numActions, state->numActions);
        printf("TEST: actions unchanged.\n");
    }

    // test option of action card
    else {
        printf("CASE: action added\n");
        
        assertTrue(numActions + 2, state->numActions);
        printf("TEST: +2 actions.\n");
        
        assertTrue(fullDeck, state->deckCount[currentPlayer]);
        printf("TEST: deck unchanged.\n");
        
        assertTrue(money, state->coins);
        printf("TEST: coins unchanged.\n");
        

    }
	return val;
}


int main() {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));


	printf("\nTests for TRIBUTE\n");
	//Random test of basic card functionality	
	for (int i = 0; i < 50; i++) {
		int seed = rand() % 1000;
		int choice2 = rand() % 2 + 1;

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		for (int j = 0; j < 20; j++) {
			int card = rand() % 20 + 1;
			gainCard(card, &G, 1, 1);
		}
		shuffle(1, &G);

		while (G.handCount[1] > 0)
		{
			discardCard(0, 1, &G, 0);
		}
		for (int j = 0; j < 5; j++) {
			drawCard(1, &G);
		}
		int random = rand() % 3;
		int revealedCard1 = G.hand[1][0];
		int revealedCard2 = G.hand[1][1];
		if (random == 0) {
			revealedCard1 = revealedCard1;
		}

		testTribute(0, revealedCard1, revealedCard2, 0, &G);
	}

	for (int i = 0; i < 10; i++) {
		int seed = rand() % 1000;
		int choice2 = rand() % 2 + 1;

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		shuffle(1, &G);

		while (G.deckCount[1] > 0)
		{
			drawCard(1, &G);
		}
		while (G.handCount[1] > 2)
		{
			discardCard(0, 1, &G, 0);
		}
		for (int j = 0; j < 2; j++) {
			drawCard(1, &G);
		}
		
		int random = rand() % 3;

		if (random == 0) {
			for (int j = 0; j < 5; j++) {
				int card = rand() % 20 + 1;
				gainCard(card, &G, 0, 1);
			}
		}

		int revealedCard1 = G.hand[1][0];
		int revealedCard2 = G.hand[1][1];
		if (random == 0) {
			revealedCard1 = revealedCard1;
		}

		testTribute(0, revealedCard1, revealedCard2, 0, &G);

	}	

	return 0;
}