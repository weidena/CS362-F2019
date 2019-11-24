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

int testMinion(int handPos, int currentPlayer, int choice1, int choice2, struct gameState *state) {
	
	int oldActions = state->numActions;
	int money = state->coins;
	int deckSize = state->deckCount[currentPlayer];
	
    int val = callMinion(choice1, choice2, state, handPos, currentPlayer);

	// Add two coins
	if (choice1 == 1) {
        printf("CASE: +2 coins\n");
		assertTrue(money + 2, state->coins);
		printf("TEST: 2 more coins.\n");
	}
	// Discard hand
	else {
		printf("CASE: Discard hand\n");
		assertTrue(state->handCount[currentPlayer], 4);
		printf("TEST: +4 cards in hand.\n");
		assertTrue(state->handCount[currentPlayer + 1], 4);
		printf("TEST: +4 cards in opponents hand.\n");
	}
	return val;
}

int main() {

	struct gameState G, tmp;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	srand(time(0));


	printf("\nTests for MINION\n");
	// test of basic card functionality	
	for (int i = 0; i < 30; i++) {
		int seed = rand() % 1000;
		int choice1 = rand() % 2;
		int choice2 = 0;
		if (!choice1) {
			choice2 = 1;
		}

		printf("\nStarting new round of tests.\n");
		initializeGame(2, k, seed, &G);
		G.handCount[1] = 5;
		memcpy(&tmp, &G, sizeof(struct gameState));
		testMinion(0, 0, choice1, choice2, &G);
		assertTrue(tmp.handCount[1], G.handCount[1]);
		printf("Test: Other players hand count changed.");
	}


	for (int i = 0; i < 10; i++) {
		int seed = rand() % 1000;
		int choice1 = rand() % 2;
		int choice2 = 0;
		if (!choice1) {
			choice2 = 1;
		}
		printf("\nStarting new round of tests - Opponent has 4 cards already\n");
		initializeGame(2, k, seed, &G);
		G.handCount[1] = 3;
		memcpy(&tmp, &G, sizeof(struct gameState));
		testMinion(0, 0, choice1, choice2, &G);
		assertTrue(G.handCount[1], 3);
		printf("Test: Other players hand count did not change.");
	}

}