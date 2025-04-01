CC=gcc
CFLAGS=-Wall -std=c99 -ggdb
LDFLAGS=-lm 

dashboard: dashboard.o DB.o DB_impl.o
	$(CC) $(CFLAGS) -o dashboard dashboard.o DB.o DB_impl.o

dashboard.o: dashboard.c
	$(CC) $(CFLAGS) -c dashboard.c

DB.o: DB.c
	$(CC) $(CFLAGS) -c DB.c 

DB_impl.o: DB_impl.c
	$(CC) $(CFLAGS) -c DB_impl.c

testing: testTable testNeighbourhood testImport

testTable: testing/testTable.c DB.o DB_impl.o
	$(CC) $(CFLAGS) -o testing/testTable testing/testTable.c DB.o DB_impl.o
	./testing/testTable > testing/testTableOut
	diff testing/testTableOut testing/correctTable

testNeighbourhood: testing/testNeighbourhood.c DB.o DB_impl.o
	$(CC) $(CFLAGS) -o testing/testNeighbourhood testing/testNeighbourhood.c DB.o DB_impl.o
	./testing/testNeighbourhood > testing/testNeighbourhoodOut
	diff testing/testNeighbourhoodOut testing/correctNeighbourhood

testImport: testing/test_importDB.c DB.o DB_impl.o
	$(CC) $(CFLAGS) -o testing/test_import testing/test_importDB.c DB.o DB_impl.o

clean:
	rm dashboard *.o testing/test*Out
