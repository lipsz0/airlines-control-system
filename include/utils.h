#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

// Limpa a tela do terminal
void clear_terminal(void);

// Limpa o buffer de entrada
void clear_buffer(void);

// Remove nova linha de string
void remove_newline(char *str);

// Converte string para maiusculas
void to_upper_format(char *str);

// Converte string para minusculas
void to_lower_format(char *str);

// Obtem o ano atual
unsigned int get_current_year(void);

// Aguarda o usuario pressionar ENTER
void wait_for_enter(void);

#endif