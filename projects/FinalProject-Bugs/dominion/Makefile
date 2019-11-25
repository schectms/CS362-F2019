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

bug2: bug2.c interface.o
	gcc -o bug2 bug2.c -g dominion.o rngs.o interface.o $(CFLAGS)

bug3: bug3.c interface.o
	gcc -o bug3 bug3.c -g dominion.o rngs.o interface.o $(CFLAGS)

bug4: bug4.c interface.o
	gcc -o bug4 bug4.c -g dominion.o rngs.o interface.o $(CFLAGS)

bug5: bug5.c dominion.o rngs.o 
	gcc -o bug5 bug5.c -g dominion.o rngs.o $(CFLAGS)

bug6: bug6.c dominion.o rngs.o
	gcc -o bug6 bug6.c -g dominion.o rngs.o $(CFLAGS)

bug7: bug7.c dominion.o rngs.o
	gcc -o bug7 bug7.c -g dominion.o rngs.o $(CFLAGS)

bug8: bug8.c interface.o
	gcc -o bug8 bug8.c -g dominion.o rngs.o interface.o $(CFLAGS)

bug9: bug9.c interface.o
	gcc -o bug9 bug9.c -g dominion.o rngs.o interface.o $(CFLAGS)

bug10: bug10.c interface.o
	gcc -o bug10 bug10.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player bug2 bug3 bug4 bug8 bug9 bug10

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe bug3 bug2
