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
	
    // initialize gameState for test
	struct gameState gTest;
	memcpy(&gTest, state, sizeof(struct gameState));

	int val = minionEffect(choice1, state, currentPlayer, handPos);

	// Add two coins
	if (choice1 == 1) {
        printf("CASE: +2 coins\n");
		assertTrue(gTest.coins + 2, state->coins);
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

	struct gameState G;
	srand(time(0));


	printf("\nTESTS FOR MINION\n");
	for (int i = 0; i < 2000; i++) {
		for (int j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}

		//initialize numBuys and coins
		G.numBuys = floor(Random() * 256);
		G.coins = floor(Random() * 256);

		//initialize supply cards
		for (int j = 0; j < 27; j++) {
			G.supplyCount[j] = floor(Random() * 500);
		}

		int choice1 = floor(Random() * 2);
		int player = ((int)floor(Random() * 500) % 3) + 2;
		G.numPlayers = player;

		// initialize player's cards
		for (int j = 0; j <= player; j++) {
			G.handCount[j] = 0;
			G.deckCount[j] = 0;
			G.discardCount[j] = 0;
			int limit = floor(Random() * 500);
			for (int k = 0; k < limit; k++) {
				int supplyPos = floor(Random() * 27);
				int toFlag = floor(Random() * 3);
				gainCard(supplyPos, &G, toFlag, j);
			}
		}
        
		int choice2 = floor(Random() * G.handCount[player]);
		G.playedCardCount = 0;
		G.whoseTurn = player;

		testMinion(0, player, choice1, choice2, &G);
	}
}