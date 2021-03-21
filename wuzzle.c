/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "io.h"

#define NUMARGS 2

int main(int argc, char* argv[]) {
    /* check the command line args and then pass the appropriate arg to
     * play_game()
     **/
    if (argc != NUMARGS + 1) {
        error_print(
            "Incorrect amount of arguments passed. Please include a valid"
            " word_scores file and a words_ file\n");
        return EXIT_FAILURE;
    }

    normal_print(
        "---------------------------------------------\n"
        "| Hello - Welcome to the WUZZLE SPELLCHECK! |\n"
        "---------------------------------------------\n");

    srand(time(NULL));

    play_game(argv[1], argv[2]);

    return EXIT_SUCCESS;
}