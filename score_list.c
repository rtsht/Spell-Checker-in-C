/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include "score_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "io.h"

/**
 * returns a malloced list of the scores loaded in from disk. As this is file io
 * you need to validate file data to ensure it is valid. Do not however validate
 *the file name.
 **/
struct score_list *load_scores(const char *filename) {
    FILE *scores;
    struct score_list *thelist;
    char line[LINELEN + EXTRACHARS];
    int line_count = 0;
    int sum_total_count = 0;

    scores = open_file_read(filename);
    if (scores == NULL) {
        return NULL;
    }
    /* Allocating memory for the score list */
    thelist = (struct score_list *)malloc(sizeof(struct score_list));
    if (thelist == NULL) {
        perror("Failed to allocate memory");
        fclose(scores);
        return NULL;
    }
    /* Read the file line by line */
    while (fgets(line, LINELEN + EXTRACHARS, scores) != NULL) {
        char *input;
        int input_int;

        if (line_count == NUM_SCORES) {
            error_print("Too many letters in the supplied file\n");
            free(thelist);
            fclose(scores);
            return NULL;
        }
        /* Getting the first element - the letter */
        input = strtok(line, DELIM);
        if (input[0] < 'A' || input[0] > 'Z') {
            error_print("Letter out of range\n");
            free(thelist);
            fclose(scores);
            return NULL;
        }
        thelist->scores[line_count].letter = input[0];
        /* Getting the second element - the count of those letters that will be
         * available */
        input = strtok(NULL, DELIM);
        if (!str_to_int(input, &input_int)) {
            error_print("Invalid score in file for '%c'\n",
                        thelist->scores[line_count].letter);
            free(thelist);
            fclose(scores);
            return NULL;
        }
        thelist->scores[line_count].score = input_int;
        /* Getting the third element - The score attributed to that letter */
        input = strtok(NULL, DELIM);
        if (input[strlen(input) - 1] == '\n') { /* A \n is in the end of line*/
            input[strlen(input) - 1] = '\0';
        }
        if (!str_to_int(input, &input_int)) {
            error_print("Invalid count in file for '%c'\n",
                        thelist->scores[line_count].letter);
            free(thelist);
            fclose(scores);
            return NULL;
        }
        thelist->scores[line_count].count = input_int;
        sum_total_count += input_int;
        line_count++;
    }
    if (line_count < NUM_SCORES) {
        error_print("Not enough letters in the supplied file\n");
        free(thelist);
        fclose(scores);
        return NULL;
    }
    if (unique_check(thelist) == FALSE) {
        error_print("Found two occurances of the same letter\n");
        free(thelist);
        fclose(scores);
        return NULL;
    }
    fclose(scores);
    thelist->num_scores = NUM_SCORES;
    thelist->total_count = sum_total_count;
    return thelist;
}

int get_rand_letter(struct score_list *thelist) {
    int rand;
    do {
        rand = get_rand_int(thelist->num_scores);
    } while (thelist->scores[rand].count == 0);
    thelist->scores[rand].count--;
    return thelist->scores[rand].letter;
}

BOOLEAN unique_check(struct score_list *thelist) {
    int i, j;

    for (i = 0; i < NUM_SCORES; i++) {
        for (j = 0; j < NUM_SCORES; j++) {
            if (i != j) {
                if (thelist->scores[i].letter == thelist->scores[j].letter) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

void free_score_list(struct score_list *thelist) { free(thelist); }
