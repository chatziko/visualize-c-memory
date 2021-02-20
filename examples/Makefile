# options
CC = gcc
CFLAGS = -Wall -g 

# This allows to wrap malloc & free (see malloc-wrapper.c) so that we can track heap allocations
LDFLAGS = -Wl,--wrap=malloc -Wl,--wrap=free

OBJS = examples.o ../visualize-c-memory/malloc-wrapper.o
EXEC = examples

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
