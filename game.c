/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include "game.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * initialise the game. Please see the assignment specification for details of
 * what is required.
 **/
BOOLEAN game_init(struct game *thegame, char *scorefilename,
                  char *wordfilename) {
    clock_t start, end;
    double elapsed;

    /* Scores initialisation and timing */
    start = clock();
    thegame->scorelist = load_scores(scorefilename);
    if (thegame->scorelist == NULL) {
        error_print("Scores list failed to initialise\n");
        return FALSE;
    }
    end = clock();
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    normal_print("Time taken to load scores is %f\n", elapsed);

    /* Word list initialisation and timing */
    start = clock();
    thegame->wordlist = load_words(wordfilename);
    if (thegame->wordlist == NULL) {
        error_print("Word list failed to initialise\n");
        free_score_list(thegame->scorelist);
        return FALSE;
    }
    end = clock();
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    normal_print("Time taken to load words is %f\n", elapsed);

    return TRUE;
}

/**
 * the core function for the management of the game.
 *
 * call game_init() to initialise the game and then manage whose player turn
 * it is and handle cleaning up and quitting the program when a player quits the
 * game.
 **/
void play_game(char *scorefilename, char *wordfilename) {
    struct game thegame;
    BOOLEAN exit = FALSE;

    /* Game initialisation */
    if (!game_init(&thegame, scorefilename, wordfilename)) {
        error_print("Game init failed\n");
        return;
    }

    /* The main game loop */
    while (exit == FALSE) {
        char input[LINELEN + EXTRACHARS];
        char *option;
        char *arg;
        enum input_result input_res;
        char *pinput = input;

        normal_print(
            "\n[type :help for more commands]\n"
            "Please enter a word to see if it is in the word list: ");
        do {
            input_res = get_input_string(input);
        } while (!input_res);
        if (input_res == IR_EOF) {
            normal_print("\n");
            exit = TRUE;
            continue;
        }
        while (isspace((char)*pinput)) {
            pinput++;
        }
        /* Menu commands */
        if (pinput[0] == ':') {
            option = strtok(pinput, " ");
            arg = strtok(NULL, " ");
            if (strtok(NULL, " ") != NULL) {
                error_print(
                    "Too many arguments entered. Enter ':help' for proper "
                    "usage\n");
                continue;
            }
            command_menu(&thegame, option, arg);
            continue;
        }
        /* Spell checker */
        str_to_uppr(pinput);
        if (input_res != IR_BLANK) {
            if (is_in_dictionary(thegame.wordlist, pinput)) {
                normal_print("Success, '%s' is in the list!\n", pinput);
            } else {
                normal_print("Unfortunately, '%s' is not in the list\n",
                             pinput);
            }
        }
    }
    end_game(&thegame, wordfilename);
}

void command_menu(struct game *thegame, char *input, char *arg) {
    clock_t start, end;
    double elapsed;

    /* HELP command */
    if (strcmp(input, ":help") == 0) {
        normal_print("\n------------------------\n");
        normal_print("Command usage:\n");
        normal_print(
            "\t:add myword    - Adds the word 'myword' to the loaded word "
            "list\n");
        normal_print(
            "\t:delete myword - Removes the word 'myword' from the loaded "
            "word list\n");
        normal_print(
            "\t:save filename - Saves the current word list to the file "
            "'filename'\n");
        normal_print(
            "\nctrl+d will exit the program after saving the current list to "
            "the supplied file\n");
        normal_print("------------------------\n");

        /* ADD command */
    } else if (strcmp(input, ":add") == 0) {
        if (arg == NULL) {
            error_print("You must supply a word to add it to the list\n");
            return;
        }
        if (is_alph_str(arg) == FALSE) {
            error_print("The word must contain letters only\n");
            return;
        }
        if (is_in_dictionary(thegame->wordlist, arg) == TRUE) {
            error_print("'%s' is already in the word list\n", arg);
            return;
        } else {
            if (word_list_add(thegame->wordlist, arg) == TRUE) {
                normal_print(
                    "Success!!! '%s' has been added to the word list\n", arg);
            } else {
                error_print("'%s' not added to the list!\n");
            }
        }

        /* DELETE command */
    } else if (strcmp(input, ":delete") == 0) {
        if (arg == NULL) {
            error_print("You must supply a word to delete it from the list\n");
            return;
        }
        if (is_alph_str(arg) == FALSE) {
            error_print("The word must contain letters only\n");
            return;
        }
        if (is_in_dictionary(thegame->wordlist, arg) == TRUE) {
            if (word_list_remove(thegame->wordlist, arg) == TRUE) {
                normal_print(
                    "Success!!! '%s' has been removed from the current word "
                    "list\n",
                    arg);
            }
        } else {
            error_print("'%s' is not in the current word list\n", arg);
        }

        /* SAVE command */
    } else if (strcmp(input, ":save") == 0) {
        if (arg == NULL) {
            error_print("You must supply a filename to save the list to\n");
            return;
        }
        start = clock();
        if (save_list(arg, thegame->wordlist) == TRUE) {
            end = clock();
            elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
            normal_print("Success! List saved to '%s' in %f secs\n", arg,
                         elapsed);
        }
    } else {
        normal_print("Invalid command. Use ':help' for instructions...\n");
    }
}

void end_game(struct game *thegame, char *wordfilename) {
    normal_print("Exiting the Game...\n");
    free_score_list(thegame->scorelist);
    if (thegame->wordlist != NULL) {
        if (save_list(wordfilename, thegame->wordlist) == TRUE) {
            normal_print("Success! List saved to '%s'", wordfilename);
        } else {
            error_print("there was an error saving to '%s'", wordfilename);
        }
    }
    free_word_list(thegame->wordlist);
}
