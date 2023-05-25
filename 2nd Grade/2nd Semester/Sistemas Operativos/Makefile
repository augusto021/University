CC = gcc
CFLAGS = -Wall -g

all: server client execs

server: sdstored

client: sdstore

execs:
		$(MAKE) all -C SDStore-transf

sdstored: src/sdstored.c
		$(CC) $(CFLAGS) src/sdstored.c src/sharedFunction.c -o bin/sdstored

sdstore: src/sdstore.c
		$(CC) $(CFLAGS) src/sdstore.c src/sharedFunction.c -o bin/sdstore

clean:
		rm -f bin/*
		$(MAKE) clean -C SDStore-transf


runS:
		./bin/sdstored etc/config.txt SDStore.transf/

runC:
		./bin/sdstore