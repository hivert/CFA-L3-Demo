# Fichier  : Makefile
# Auteur   : Florent Hivert
# A propos : DEUG S4 Math/Info Option Info
#            gestion de listes chainées
# Date     : ven fév  4 13:54:53 CET 2000
#######################################################

SHELL = /bin/sh
CFLAGS = -Wall -lrt -O3 # -pg -g
CC = gcc

#### Fichiers ####
LIB_FILES = lists_dh.c mergesort_dh.c
C_FILES = $(LIB_FILES:.c=.c) demo.c
H_FILES = $(LIB_FILES:.c=.h)
O_FILES = $(LIB_FILES:.c=.o)
SRCS = $(C_FILES) $(H_FILES)
MAIN_FILE = demo


#### Pour que les .c dépendent des .h ####
%.o : %.c %.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@



#### Dépendances ####
.PHONY: clean all
all: $(MAIN_FILE)

demo: $(O_FILES) 



#### Cibles diverses ####
clean:
	$(RM) $(O_FILES) $(MAIN_FILE)
TAGS: $(SRCS)
	etags $(SRCS)
check: demo
	./demo
