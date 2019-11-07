CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testUnitTest1: unittest1.c dominion.o rngs.o
	gcc  -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unit1 &> unittestresult1.out
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out
	
testUnitTest2: unittest2.c dominion.o rngs.o
	gcc  -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unit2 &> unittestresult2.out
	gcov dominion.c >> unittestresult2.out
	cat dominion.c.gcov >> unittestresult2.out

testDrawCard: testdrawcard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
