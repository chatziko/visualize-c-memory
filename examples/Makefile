# options
CC = gcc
CFLAGS = -Wall -g 

LIB = ../src
OBJS = examples.o
EXEC = examples

$(EXEC): $(OBJS) $(LIB)/visualize-c-memory.so
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

$(LIB)/visualize-c-memory.so:
	$(MAKE) -C $(LIB) visualize-c-memory.so

clean:
	rm -f $(OBJS) $(EXEC)
