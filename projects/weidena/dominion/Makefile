CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)

randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtest1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtest2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtest3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtest3 randomtestcard3.c dominion.o rngs.o $(CFLAGS)

randomTest1: randomtestcard1.c dominion.o rngs.o
	gcc  -o randUnit1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randUnit1 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	
randomTest2: randomtestcard2.c dominion.o rngs.o
	gcc  -o randUnit2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randUnit2 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out

randomTest3: randomtestcard3.c dominion.o rngs.o
	gcc  -o randUnit3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./randUnit3 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittests
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unitetestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

randomtestresults: clean all randomTest1 randomTest2 randomTest3
	cat dominion.c.gcov >> randomtestresults.out