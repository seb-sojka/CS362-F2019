CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unit8 unit9 unit10 unit11

unitTest1: unittestbug1.c dominion.o rngs.o
	gcc  -o unit1 -g  unittestbug1.c dominion.o rngs.o $(CFLAGS)
	./unit1 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest2: unittestbug2.c dominion.o rngs.o
	gcc  -o unit2 -g  unittestbug2.c dominion.o rngs.o $(CFLAGS)
	./unit2 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest3: unittestbug3.c dominion.o rngs.o
	gcc  -o unit3 -g  unittestbug3.c dominion.o rngs.o $(CFLAGS)
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

unitTest6: unittest6.c dominion.o rngs.o
	gcc  -o unit6 -g  unittest6.c dominion.o rngs.o $(CFLAGS)
	./unit6 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest7: unittest7.c dominion.o rngs.o
	gcc  -o unit7 -g  unittest7.c dominion.o rngs.o $(CFLAGS)
	./unit7 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest8: unittest8.c dominion.o rngs.o
	gcc  -o unit8 -g  unittest8.c dominion.o rngs.o $(CFLAGS)
	./unit8 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest9: unittest9.c dominion.o rngs.o
	gcc  -o unit9 -g  unittest9.c dominion.o rngs.o $(CFLAGS)
	./unit9 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest10: unittest10.c dominion.o rngs.o
	gcc  -o unit10 -g  unittest10.c dominion.o rngs.o $(CFLAGS)
	./unit10 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unitTest11: unittest11.c dominion.o rngs.o
	gcc  -o unit11 -g  unittest11.c dominion.o rngs.o $(CFLAGS)
	./unit11 >> unittestresult.out
	gcov dominion.c -b -f>> unittestresult.out

unittestresults: clean all unitTest1 unitTest2 unitTest3 unitTest4 unitTest5 unitTest6 unitTest7 unitTest8 unitTest9 unitTest10 unitTest11
	cat dominion.c.gcov >> unittestresult.out

