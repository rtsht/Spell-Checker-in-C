/******************************************************************************
 * Student Name    : Andrew Waltos
 * RMIT Student ID : s3791004
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 1, study period 4, 2020. Adapted for use in Assignment 3.
 *****************************************************************************/
#include <stdarg.h>
#include <string.h>

#include "shared.h"

#ifndef IO_H
#define IO_H
/**
 * the choices that can be made from the menu. Do not hardcode the values - use
 * these constants. Hardcoding of values is poor practice and makes your code
 * very difficult to maintain.
 **/
enum menu_choice {
    MC_REVERSE,
    MC_MAGSQ,
    MC_GR_KNAP,
    MC_BF_KNAP,
    MC_QUIT,
    MC_INVALID = -1
};

/**
 * enumeration provided to you to return the result an input operation.
 **/
enum input_result { IR_FAILURE, IR_SUCCESS, IR_BLANK, IR_EOF = -1 };

#define LINELEN 80
#define EXTRACHARS 2
#define ARRAY_SHIFT 1
#define DECIMAL 10

int get_rand_int(int);
enum input_result get_input_string(char *);
BOOLEAN str_to_int(char *, int *);
void str_to_uppr(char *);
BOOLEAN is_alph_str(char *);
FILE *open_file_read(const char *);
FILE *open_file_write(const char *);
int error_print(const char *format, ...);
int normal_print(const char *format, ...);
void clear_buffer(void);

/**
 * declare functions here that handle the input for each option. For now each
 * function will just say "hello from <option_name>" (where option_name is the
 * name of the option being called) but the first thing you will want to do in
 * part 3 is to implement these function to handle the user input for each
 * function.
 **/

#endif
