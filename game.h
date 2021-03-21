/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include "io.h"
#include "score_list.h"
#include "word_list.h"

#ifndef GAME_H
#define GAME_H
#define MAX_PLAYERS 2

struct game {
    struct score_list *scorelist;
    struct word_list *wordlist;
};

BOOLEAN game_init(struct game *, char *, char *);
void play_game();
void command_menu(struct game *, char *, char *);
void end_game(struct game *, char *);
#endif
