CC=gcc
CFLAGS=-Wall -std=c99
LDFLAGS=-lm 

dashboard: dashboard.c DB.o DB_impl.o
	$(CC) $(CFLAGS) -o dashboard dashboard.c DB.o DB_impl.o

DB.o: DB.c
	$(CC) $(CFLAGS) -c DB.c 

DB_impl.o: DB_impl.c
	$(CC) $(CFLAGS) -c DB_impl.c

clean:
	rm dashboard *.o