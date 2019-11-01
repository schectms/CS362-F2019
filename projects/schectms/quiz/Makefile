cc=gcc
CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	$(CC) -o testme testme.c $(CFLAGS)

runtests: testme
	./testme &> testresults.out
	gcov -b -f testme.c >>  testresults.out
	
clean:
	rm -f *.o testme *.out *.gcov *.gcda
