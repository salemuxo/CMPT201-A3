CC=gcc
CFLAGS=-Wall -std=c99
LDFLAGS=-lm 

dashboard: dashboard.o DB.o DB_impl.o
	$(CC) $(CFLAGS) -o dashboard dashboard.o DB.o DB_impl.o

dashboard.o: dashboard.c
	$(CC) $(CFLAGS) -c dashboard.c

DB.o: DB.c
	$(CC) $(CFLAGS) -c DB.c 

DB_impl.o: DB_impl.c
	$(CC) $(CFLAGS) -c DB_impl.c

testing: testTable testImport


testTable: testing/testTable.c DB.o DB_impl.o
	$(CC) $(CFLAGS) -o testing/testTable testing/testTable.c DB.o DB_impl.o 
testImport: testing/test_importDB.c DB.o DB_impl.o
	$(CC) $(CFLAGS) -o testing/test_import testing/test_importDB.c DB.o DB_impl.o


clean:
	rm -f dashboard *.o testing/testTable testing/test_import
