#include "../include/utils.h"
#include <string.h>

// Limpa a tela do terminal (compativel com Linux/Unix)
void clear_terminal(void) { system("clear"); }

// Limpa o buffer de entrada (stdin) para evitar leitura de lixo
void clear_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Remove o caractere de nova linha (\n) do final de uma string
void remove_newline(char *str) { *(str + strlen(str) - 1) = '\0'; }

// Converte todos os caracteres de uma string para maiusculas
void to_upper_format(char *str) {
  for (int i = 0; *(str + i) != '\0'; i++) {
    *(str + i) = toupper(*(str + i));
  }
}

// Converte todos os caracteres de uma string para minusculas
void to_lower_format(char *str) {
  for (int i = 0; *(str + i) != '\0'; i++) {
    *(str + i) = tolower(*(str + i));
  }
}

// Retorna o ano atual do sistema
unsigned int get_current_year(void) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  return tm.tm_year + 1900;
}

// Aguarda o usuario pressionar ENTER
void wait_for_enter(void) {
  printf("\nPressione ENTER para continuar...");
  getchar();
}