#ifndef UTILS_H
#define UTILS_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

// Function to clear the terminal screen
void clear_terminal (void);

// Function to clear the input buffer
void clear_buffer (void);

// Function to retire newline character from a string
void retire_newline (char *str);

// Function to convert a string to lowercase and format it
void tolower_format (char *str);

// Function to get the current year
unsigned int get_current_year (void);

#endif