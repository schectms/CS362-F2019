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

randomtest1: randomtestcard1.c interface.o
	gcc -o randomtest1 randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomtest2: randomtestcard2.c interface.o
	gcc -o randomtest2 randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomtest3: randomtestcard3.c interface.o
	gcc -o randomtest3 randomtestcard3.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtest1 randomtest2 randomtest3

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
