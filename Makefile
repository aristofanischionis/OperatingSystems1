#Got this from the official Website of Alexis Delis

OBJS 	= main.o FileHandling.o API.o HashTable.o Node.o Prime.o
SOURCE	= main.c CodeFiles/FileHandling.c CodeFiles/API.c Graph/HashTable.c Graph/Node.c Graph/Prime.c
HEADER  = HeaderFiles/HashTable.h HeaderFiles/FileHandling.h HeaderFiles/API.h HeaderFiles/Node.h HeaderFiles/Prime.h
OUT  	= mygraph
CC	= gcc
FLAGS   = -g -c -Wall
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

FileHandling.o: CodeFiles/FileHandling.c
	$(CC) $(FLAGS) CodeFiles/FileHandling.c

API.o: CodeFiles/API.c
	$(CC) $(FLAGS) CodeFiles/API.c

HashTable.o: Graph/HashTable.c
	$(CC) $(FLAGS) Graph/HashTable.c

Node.o: Graph/Node.c
	$(CC) $(FLAGS) Graph/Node.c

Prime.o: Graph/Prime.c
	$(CC) $(FLAGS) Graph/Prime.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
