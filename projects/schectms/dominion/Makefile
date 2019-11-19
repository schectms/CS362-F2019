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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unitTest1: unitTest1.c interface.o 
	gcc -o unitTest1 -g unitTest1.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest2: unitTest2.c interface.o 
	gcc -o unitTest2 -g unitTest2.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest3: unitTest3.c interface.o
	gcc -o unitTest3 -g unitTest3.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest4: unitTest4.c interface.o
	gcc -o unitTest4 -g unitTest4.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest5: unitTest5.c interface.o
	gcc -o unitTest5 -g unitTest5.c dominion.o rngs.o interface.o $(CFLAGS)


unitTestResults: unitTest1 unitTest2 unitTest3 unitTest4 unitTest5
	./unitTest1 &> unittestresult.out
	./unitTest2 >> unittestresult.out
	./unitTest3 >> unittestresult.out
	./unitTest4 >> unittestresult.out
	./unitTest5 >> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out

all: playdom player unitTest1 unitTest2 unitTest3 unitTest4 unitTest5 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
