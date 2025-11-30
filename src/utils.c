#include "../include/utils.h"

void clear_terminal (void) { system ("clear"); }

void clear_buffer (void) {
    int c;
    while ((c = getchar ()) != '\n' && c != EOF);
}

void retire_newline (char *str) { *(str + strlen (str) - 1) = '\0'; }

void tolower_format (char *str) {
    for (int i = 0; *(str + i) != '\0'; i++) {
        *(str + i) = tolower (*(str + i));
    }
}

unsigned int get_current_year (void) {
    time_t t = time (NULL);
    struct tm tm = *localtime (&t);
    return tm.tm_year + 1900;
}