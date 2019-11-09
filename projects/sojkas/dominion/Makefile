CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

unitTest1: unittest1.c dominion.o rngs.o
	gcc  -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unit1 &> unittestresult1.out
	gcov dominion.c -b -f>> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out
	
unitTest2: unittest2.c dominion.o rngs.o
	gcc  -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unit2 &> unittestresult2.out
	gcov dominion.c -b -f>> unittestresult2.out
	cat dominion.c.gcov >> unittestresult2.out
	
unitTest3: unittest3.c dominion.o rngs.o
	gcc  -o unit3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unit3 &> unittestresult3.out
	gcov dominion.c -b -f>> unittestresult3.out
	cat dominion.c.gcov >> unittestresult3.out
	
unitTest4: unittest4.c dominion.o rngs.o
	gcc  -o unit4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unit4 &> unittestresult4.out
	gcov dominion.c -b -f>> unittestresult4.out
	cat dominion.c.gcov >> unittestresult4.out

unitTest5: unittest5.c dominion.o rngs.o
	gcc  -o unit5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
	./unit2 &> unittestresult5.out
	gcov dominion.c -b -f>> unittestresult5.out
	cat dominion.c.gcov >> unittestresult5.out

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
