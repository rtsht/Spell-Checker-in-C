/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 3, study period 4, 2020.
 *****************************************************************************/
#include "word_list.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

/* create the functions for the management of the linked list in this file */
struct word_list *load_words(const char *filename) {
    FILE *words;
    struct word_list *wordlist;

    /* Open the file */
    words = open_file_read(filename);
    if (words == NULL) {
        return NULL;
    }
    /* Allocating memory for the word list */
    wordlist = (struct word_list *)malloc(sizeof(struct word_list));
    if (wordlist == NULL) {
        perror("Failed to allocate memory");
        fclose(words);
        return NULL;
    }
    word_list_init(wordlist);
    /* Add the words */
    while (!feof(words)) {
        char nextword[LINELEN + EXTRACHARS];
        while (fgets(nextword, LINELEN + EXTRACHARS, words) != NULL) {
            if (nextword[strlen(nextword) - 1] != '\n') {
                error_print("Line length too long in file\n");
                fclose(words);
                return NULL;
            }
            nextword[strlen(nextword) - 1] = '\0';
            if (word_list_add(wordlist, nextword) == FALSE) {
                error_print("Failed to add the word '%s'\n", nextword);
                fclose(words);
                return NULL;
            }
        }
    }
    fclose(words);
    return wordlist;
}

BOOLEAN save_list(char *filename, struct word_list *wordlist) {
    FILE *words;
    struct word_node *current = wordlist->head;

    /* Open the file */
    words = open_file_write(filename);
    if (words == NULL) {
        return FALSE;
    }
    while (current) {
        fputs(current->word, words);
        fputs("\n", words);
        current = current->next;
    }
    fclose(words);
    return TRUE;
}

void word_list_init(struct word_list *wordlist) {
    assert(wordlist);
    wordlist->head = NULL;
    wordlist->num_words = 0;
}

BOOLEAN word_list_add(struct word_list *wordlist, const char *newword) {
    struct word_node *new_node;
    struct word_node *current_node;
    struct word_node *prev_node = NULL;

    assert(wordlist);
    assert(newword);
    /* Allocating memory for the new node */
    new_node = malloc(sizeof(struct word_node));
    if (new_node == NULL) {
        perror("Failed to allocate memory for a new node");
        return FALSE;
    }
    /* Allocating memory for the new word */
    new_node->word = malloc(sizeof(char) * strlen(newword) + 1);
    if (new_node->word == NULL) {
        perror("Failed to allocate memory for a new word");
        return FALSE;
    }
    strcpy(new_node->word, newword);
    new_node->next = NULL;
    /* This is the case if the list is empty and this will be the first
     * insertion */
    if (wordlist->head == NULL) {
        wordlist->head = new_node;
        wordlist->num_words++;
        return TRUE;
    }
    current_node = wordlist->head;
    /* Iterate through the wordlist until either we get to the end or before we
     * get to a node where the word is alphabetically lower than the word we
     * want to add */
    while (current_node != NULL && strcmp(current_node->word, newword) < 0) {
        prev_node = current_node;
        current_node = current_node->next;
    }
    /* If the previous node is NULL then we havent moved in our above iteration,
     * therefore we should insert the new word at the beginning of the wordlist
     */
    if (prev_node == NULL) {
        new_node->next = wordlist->head;
        wordlist->head = new_node;
    }
    /* If the current node is NULL then we are at the end of the wordlist and
     * can just plonk the new node here by setting the previous node's next
     * pointer to the new one */
    else if (current_node == NULL) {
        prev_node->next = new_node;
        /* Otherwise, we are somewhere between the start and end of the wordlist
         * and will insert the new node at this spot by setting it's previous
         * node's next to the new node and the new node's next to the current
         * one */
    } else {
        prev_node->next = new_node;
        new_node->next = current_node;
    }
    wordlist->num_words++;
    return TRUE;
}

BOOLEAN word_list_remove(struct word_list *wordlist, const char *word) {
    struct word_node *current = wordlist->head;
    struct word_node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            /* This is the case if we are at the start of the list */
            if (prev == NULL) {
                wordlist->head = current->next;
                free(current->word);
                free(current);
                return TRUE;
                /* Else we are somewhere in the middle or at the end */
            } else {
                prev->next = current->next;
                free(current->word);
                free(current);
                return TRUE;
            }
        }
        prev = current;
        current = current->next;
    }
    return FALSE;
}

void print_word_list(struct word_list *wordlist) {
    struct word_node *current = wordlist->head;

    normal_print("---------LIST---------\n");
    while (current != NULL) {
        char *word = current->word;
        normal_print("%s\n", word);
        current = current->next;
    }
    normal_print("----------------------\n\n");
}

/**
 * tests whether the word specified is in the word_list and therefore a valid
 * spelling. Please see the assignment specification for further details.
 **/
BOOLEAN is_in_dictionary(struct word_list *thelist, const char *word) {
    struct word_node *current = thelist->head;

    str_to_uppr((char *)word);
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

void free_word_list(struct word_list *wordlist) {
    struct word_node *current_node = wordlist->head;
    struct word_node *temp_node = NULL;

    while (current_node != NULL) {
        temp_node = current_node->next;
        free(current_node->word);
        free(current_node);
        current_node = temp_node;
    }
    free(wordlist);
}