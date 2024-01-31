CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = ville.o
EXECS = t_AVL_nbTrajets t_AVL_ordreAlpha S_AVL S_CALCUL

all: $(EXECS)

t_AVL_nbTrajets: $(OBJS) t_avl_nbTrajets.c
	$(CC) $(CFLAGS) -o t_AVL_nbTrajets $(OBJS) t_avl_nbTrajets.c

t_AVL_ordreAlpha: $(OBJS) t_avl_ordreAlpha.c
	$(CC) $(CFLAGS) -o t_AVL_ordreAlpha $(OBJS) t_avl_ordreAlpha.c

S_AVL: $(OBJS) s_avl.c stats.c stats.h
	$(CC) $(CFLAGS) -o S_AVL $(OBJS) s_avl.c stats.c

S_CALCUL: $(OBJS) s_calcul.c stats.c stats.h
	$(CC) $(CFLAGS) -o S_CALCUL $(OBJS) s_calcul.c stats.c

ville.o: ville.c ville.h
	$(CC) $(CFLAGS) -c ville.c

clean:
	rm -f $(EXECS) $(OBJS)
