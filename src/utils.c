#include "../include/utils.h"
#include <string.h>

// Limpa terminal
void clear_terminal(void) { system("clear"); }

// Limpa buffer
void clear_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Remove newline
void remove_newline(char *str) { *(str + strlen(str) - 1) = '\0'; }

// Para maiusculas
void to_upper_format(char *str) {
  for (int i = 0; *(str + i) != '\0'; i++) {
    *(str + i) = toupper(*(str + i));
  }
}

// Para minusculas
void to_lower_format(char *str) {
  for (int i = 0; *(str + i) != '\0'; i++) {
    *(str + i) = tolower(*(str + i));
  }
}

// Ano atual
unsigned int get_current_year(void) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  return tm.tm_year + 1900;
}

// Aguarda ENTER
void wait_for_enter(void) {
  printf("\nPressione ENTER para continuar...");
  getchar();
}