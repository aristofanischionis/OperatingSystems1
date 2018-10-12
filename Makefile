#Got this from the official Website of Alexis Delis

OBJS 	= main.o FileHandling.o API.o
SOURCE	= main.c FileHandling.c API.c
HEADER  = MyHeader.h FileHandling.h API.h
OUT  	= mygraph
CC	= gcc
FLAGS   = -g -c -Wall
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

FileHandling.o: FileHandling.c
	$(CC) $(FLAGS) FileHandling.c

API.o: API.c
	$(CC) $(FLAGS) API.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
