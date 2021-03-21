###############################################################################
# Student Name    : Andrew Waltos
# RMIT Student ID : s3791004
#
# Startup code provided by Paul Miller for use in "Programming in C",
# Assignment 2, study period 4, 2020.
###############################################################################

# Makefile usage:
# 
# Compile and link with 'make'. 
# If debugging flags are required, use 'make debug' or 'make sanitize'.
# Clean the project with 'make clean'.

CC=gcc
CFLAGS=-ansi -Wall -pedantic
LFLAGS=

# Linking
wuzzle: wuzzle.o game.o io.o score_list.o word_list.o
	$(CC) $(LFLAGS) wuzzle.o game.o io.o score_list.o word_list.o -o wuzzle

# Compiling
wuzzle.o: wuzzle.c game.h io.h
	$(CC) $(CFLAGS) -c wuzzle.c

game.o: game.c game.h io.h score_list.h word_list.h
	$(CC) $(CFLAGS) -c game.c

io.o:io.c io.h shared.h
	$(CC) $(CFLAGS) -c io.c

score_list.o: score_list.c score_list.h io.h shared.h
	$(CC) $(CFLAGS) -c score_list.c

word_list.o: word_list.c word_list.h shared.h
	$(CC) $(CFLAGS) -c word_list.c

# Debug
debug: CFLAGS+=-g
debug: clean wuzzle

# Sanitize
sanitize: CFLAGS+=-g -fsanitize=address
sanitize: LFLAGS+=-fsanitize=address
sanitize: clean wuzzle

# Cleaning the project
.PHONY: clean
clean:
	rm -f wuzzle *.o
