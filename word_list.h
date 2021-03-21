/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 23, study period 4, 2020.
 *****************************************************************************/
#include "shared.h"
#ifndef WORDLIST_H
#define WORDLIST_H
struct word_node {
    struct word_node *next;
    char *word;
};
struct word_list {
    struct word_node *head;
    long num_words;
};

/**
 * List function prototypes that will be used for the management of the linked
 * list here.
 **/
struct word_list *load_words(const char *);
BOOLEAN save_list(char *, struct word_list *);
void word_list_init(struct word_list *);
BOOLEAN word_list_add(struct word_list *, const char *);
BOOLEAN word_list_remove(struct word_list *, const char *);
void print_word_list(struct word_list *);
BOOLEAN is_in_dictionary(struct word_list *, const char *);
void free_word_list(struct word_list *);
#endif
