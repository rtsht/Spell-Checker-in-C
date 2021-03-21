/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 1, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include "io.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Return a random int between 0 and a specified number */
int get_rand_int(int max) { return rand() % max; }

/*
 * Get a string from stdin and check for buffer overflow as well as a blank or
 * ctrl+d entry
 */
enum input_result get_input_string(char *input) {
    if (fgets(input, LINELEN + EXTRACHARS, stdin) == NULL) {
        return IR_EOF;
    }
    if (input[strlen(input) - 1] != '\n') {
        error_print("Too many characters entered\n");
        clear_buffer();
        return IR_FAILURE;
    }
    if (input[0] == '\n') {
        return IR_BLANK;
    }
    input[strlen(input) - 1] = '\0';
    return IR_SUCCESS;
}

/* Convert a string to an int after validation */
BOOLEAN str_to_int(char *input, int *int_var) {
    char *end;
    long temp_int;
    int i;

    for (i = 0; i < strlen(input); i++) {
        if (isdigit(input[i]) == FALSE) {
            return FALSE;
        }
    }
    temp_int = strtol(input, &end, DECIMAL);
    if (temp_int > INT_MAX || temp_int < INT_MIN) {
        return FALSE;
    }
    if (*end != 0 && *end != '\n') {
        return FALSE;
    }
    *int_var = (int)temp_int;
    return TRUE;
}

/* Simple char conversion to upper of a string pointer */
void str_to_uppr(char *string) {
    char uppr[LINELEN + EXTRACHARS];
    int i;

    for (i = 0; i < strlen(string) + 1; i++) {
        uppr[i] = (char)toupper(string[i]);
    }
    strcpy(string, uppr);
}

/* Check all the chars of a string pointer are alphabetic */
BOOLEAN is_alph_str(char *input) {
    int i;

    for (i = 0; i < strlen(input); i++) {
        if (isalpha(input[i]) == FALSE) {
            return FALSE;
        }
    }
    return TRUE;
}

/* Open and null check a proposed filename for reading */
FILE *open_file_read(const char *filename) {
    FILE *file;

    file = fopen(filename, "r");
    if (file == NULL) {
        char errormsg[LINELEN + EXTRACHARS];
        sprintf(errormsg, "There was a problem opening the supplied file '%s'",
                filename);
        perror(errormsg);
    }
    return file;
}

/* Open and null check a proposed filename for writing */
FILE *open_file_write(const char *filename) {
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        char errormsg[LINELEN + EXTRACHARS];
        sprintf(errormsg, "There was a problem opening the supplied file '%s'",
                filename);
        perror(errormsg);
    }
    return file;
}

/**
 * this function is a drop-in replacement for fprintf with stderr. You
 *should
 * use this and not use fprintf in your code. The idea is that while this
 * does the same thing as printf, we could replace this such as with a gui
 * function and you would not need to change any other code for it to work.
 **/
int error_print(const char *format, ...) {
    va_list arglist;
    int count = 0;
    /* print out error preamble */
    count += fprintf(stderr, "Error: ");
    /* print out the rest of the args */
    va_start(arglist, format);
    count += vfprintf(stderr, format, arglist);
    va_end(arglist);
    return count;
}

/**
 * this function is a stand-in for printf. You should use this function
 *rather
 * than printf. The idea is that we could replace this function with one
 * targeting another output and we would not have to change any other code
 *for
 * this to work.
 **/
int normal_print(const char *format, ...) {
    int count = 0;
    /* prepare the argument list for output */
    va_list arglist;
    va_start(arglist, format);
    /* output the args */
    count += vprintf(format, arglist);
    /* cleanup */
    va_end(arglist);
    return count;
}

/*
 * function used to clear the buffer when you detect buffer overflow.
 * You may notice you cannot call this function from outside this module and
 * that's by design (that's why it's static). As you should be doing all input
 * and output code in this module, there is no need to have access to this
 * function outside of the io module.
 */
void clear_buffer(void) {
    int ch;

    while (ch = getc(stdin), ch != EOF && ch != '\n')
        ;
    clearerr(stdin);
}