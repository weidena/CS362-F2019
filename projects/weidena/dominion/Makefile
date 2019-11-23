CFLAGS= -Wall -g -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtest1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtest2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtest3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtest3 randomtestcard3.c dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestresults: randomtests
	./randomtest1 &> randomtestresults.out
	./randomtest2 >> randomtestresults.out
	./randomtest3 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtests: randomtest1 randomtest2 randomtest3 
all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe