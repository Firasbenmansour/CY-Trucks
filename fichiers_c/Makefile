CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = ville.o
EXECS = t_AVL_nbTrajets t_AVL_ordreAlpha

all: $(EXECS)

t_AVL_nbTrajets: $(OBJS) t_avl_nbTrajets.c
	$(CC) $(CFLAGS) -o t_AVL_nbTrajets $(OBJS) t_avl_nbTrajets.c

t_AVL_ordreAlpha: $(OBJS) t_avl_ordreAlpha.c
	$(CC) $(CFLAGS) -o t_AVL_ordreAlpha $(OBJS) t_avl_ordreAlpha.c

ville.o: ville.c ville.h
	$(CC) $(CFLAGS) -c ville.c

clean:
	rm -f $(EXECS) $(OBJS)
