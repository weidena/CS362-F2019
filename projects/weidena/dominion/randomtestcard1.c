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

/* HELPER FUNCTIONS FOR testBaron */

//go through the discard to check number of estates
int numDiscardEstates(struct gameState *state, int currentPlayer) {

	int discardEstates = 0;
	for (int i = 0; i < state->discardCount[currentPlayer]; i++) {
		if (state->discard[currentPlayer][i] == estate) {
			discardEstates++;
		}
	}
	return discardEstates;
}

//go through the hand to check number of estatess
int getNumEstates(struct gameState *state, int currentPlayer) {

	int numEstates = 0;
	for (int i = 0; i < numHandCards(state); i++) {
		if (state->hand[currentPlayer][i] == estate) {
			numEstates++;
		}
	}
	return numEstates;
}

int testBaron(int choice1, struct gameState *state, int currentPlayer) {

	// initialize game
	struct gameState gTest;
	memcpy(&gTest, state, sizeof(struct gameState));

	int val = baronEffect(choice1, state, currentPlayer);

	//Discard estate
	if (choice1 == 1 && getNumEstates(&gTest, currentPlayer) > 0) {
		printf("CASE: Discard Estate\n");
		
		assertTrue(getNumEstates(&gTest, currentPlayer) - 1, getNumEstates(state, currentPlayer));
		printf("TEST: -1 estate from hand.\n");
		
		assertTrue(gTest.coins + 4, state->coins);
		printf("TEST: Coins + 4.\n");
		
		assertTrue(numDiscardEstates(&gTest, currentPlayer) + 1, numDiscardEstates(state, currentPlayer));
		printf("TEST: +1 estate to discard pile.\n");
	}

	//Gain estate
	else {
		printf("CASE: Gaining Estate\n");
		
		assertTrue(getNumEstates(&gTest, currentPlayer) + 1, getNumEstates(state, currentPlayer));
		printf("TEST: 1 more estate in hand.\n");
		
		assertTrue(gTest.coins, state->coins);
		printf("TEST: Coins unchanged.\n");
		
		assertTrue(supplyCount(1, &gTest) - 1, supplyCount(1, state));
		printf("TEST: 1 fewer estate in supply pile.\n");
	}

	return val;
}


int main() {

	// initialize game state
	struct gameState G;
	srand(time(0));

	printf("\nTESTS FOR BARON\n");

	PutSeed(3);
	SelectStream(2);

	for (int i = 0; i < 2000; i++) {
		for (int j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		//initializing cards in the supply
		for (int j = 0; j < 27; j++) {
			G.supplyCount[j] = floor(Random() * 10);
		}
		//initializing numBuys and coins
		G.numBuys = floor(Random() * 256);
		G.coins = floor(Random() * 256);

		//randomizing which choice the player chooses
		int choice1 = floor(Random() * 2);
		int player = floor(Random() * 3 + 2);

		G.handCount[player] = 0;
		G.deckCount[player] = 0;
		G.discardCount[player] = 0;
		G.whoseTurn = player;
		
		//initializing handCount and the current hand
		for (int j = 0; j < floor(Random() * 500); j++) {
			int supplyPos = floor(Random() * 27);
			gainCard(supplyPos, &G, 2, player);
		}

		// running the test
		testBaron(choice1, &G, player);
	}

}