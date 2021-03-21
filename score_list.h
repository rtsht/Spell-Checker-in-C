/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include "shared.h"

#ifndef SCORE_LIST_H
#define SCORE_LIST_H
/**
 * a letter score is a combination of the letter itself, its score and its count
 **/
struct score {
    int letter, score, count;
};
#define NUM_SCORES 26
#define HAND_MAX 5
#define DELIM ","
/**
 * the scores list that contains the scores for all letters and doubles as the
 * 'deck' from which letters are dealt. This is also the structure used by each
 * player to represent their hand.
 **/
struct score_list {
    struct score scores[NUM_SCORES];
    int num_scores;
    int total_count;
};

struct score_list *load_scores(const char *);
int get_rand_letter(struct score_list *);
BOOLEAN unique_check(struct score_list *);
void free_score_list(struct score_list *);
#endif
