CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

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
	
unitTest1: unittest1.c dominion.o rngs.o
	gcc  -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unit1 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out
	
unitTest2: unittest2.c dominion.o rngs.o
	gcc  -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unit2 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out
	
unitTest3: unittest3.c dominion.o rngs.o
	gcc  -o unit3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unit3 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out
	
unitTest4: unittest4.c dominion.o rngs.o
	gcc  -o unit4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unit4 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest5: unittest5.c dominion.o rngs.o
	gcc  -o unit5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
	./unit5 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randUnit1 randUnit2 randUnit3 unit1 unit2 unit3 unit4 unit5

randomtestresults: clean all randomTest1 randomTest2 randomTest3
	cat dominion.c.gcov >> randomtestresults.out

unittestresults: clean all unitTest1 unitTest2 unitTest3 unitTest4 unitTest5
	cat dominion.c.gcov >> unittestresult.out
