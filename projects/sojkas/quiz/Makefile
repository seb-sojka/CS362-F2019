CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc  -o testme -g  testme.c $(CFLAGS)

all: testme.c
	gcc  -o testme -g  testme.c $(CFLAGS)
	testme

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out

