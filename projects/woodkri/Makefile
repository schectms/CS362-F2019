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

unitTest1: unitTest1.c interface.o
	gcc -o unitTest1 unitTest1.c -g dominion.o rngs.o interface.o $(CFLAGS)

unitTest2: unitTest2.c interface.o 
	gcc -o unitTest2 unitTest2.c -g dominion.o rngs.o interface.o $(CFLAGS)

unitTest3: unitTest3.c interface.o
	gcc -o unitTest3 unitTest3.c -g dominion.o rngs.o interface.o $(CFLAGS)

unitTest4: unitTest4.c interface.o
	gcc -o unitTest4 unitTest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

unitTest5: unitTest5.c interface.o
	gcc -o unitTest5 unitTest5.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomTest1: randomtestcard1.c interface.o
	gcc -o randomTest1 randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomTest2: randomtestcard2.c interface.o 
	gcc -o randomTest2 randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomTest3: randomtestcard3.c interface.o
	gcc -o randomTest3 randomtestcard3.c -g dominion.o rngs.o interface.o $(CFLAGS)
 
testCards: unitTest1 unitTest2 unitTest3 unitTest4 unitTest5 randomTest1 randomTest2 randomTest3
	./unitTest1 &> assignment5.out
	./unitTest2 >> assignment5.out
	./unitTest3 >> assignment5.out
	./unitTest4 >> assignment5.out
	./unitTest5 >> assignment5.out
	./randomTest1
	./randomTest2
	./randomTest3
	cat test1.txt >> assignment5.out
	cat test2.txt >> assignment5.out
	cat test3.txt >> assignment5.out
	gcov -b -f dominion.c >> assignment5.out 

all: playdom player unitTest1 unitTest2 unitTest3 unitTest4 unitTest5 randomTest1 randomTest2 randomTest3

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unitTest1 unitTest2 unitTest3 unitTest4 unitTest5 randomTest1 randomTest2 randomTest3

