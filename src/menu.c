#include "../include/menu.h"
#include "../include/utils.h" // Added for clear_terminal()
#include "../include/validation.h"

// Menu principal
unsigned int main_menu(void) {
  unsigned int option;
  printf("\n=== Airlines Control System ===\n");
  printf("1. Gerenciar Aeronaves\n");
  printf("2. Gerenciar Rotas\n");
  printf("3. Relatorios e Exportacao\n");
  printf("0. Sair\n");
  read_validate_int("Escolha uma opcao: ", &option, 0, 3);
  return option;
}

unsigned int aircraft_menu(void) {
  unsigned int option;
  clear_terminal();
  printf("\n=== Gerenciar Aeronaves ===\n");
  printf("1. Cadastrar Aeronave\n");
  printf("2. Listar Aeronaves\n");
  printf("3. Buscar Aeronave (Recursivo)\n");
  printf("4. Gerenciar Manutencao\n");
  printf("5. Excluir Aeronave\n");
  printf("0. Voltar\n");
  read_validate_int("Escolha uma opcao: ", &option, 0, 5);
  return option;
}

unsigned int routes_menu(void) {
  unsigned int option;
  clear_terminal();
  printf("\n=== Gerenciar Rotas ===\n");
  printf("1. Cadastrar Rota\n");
  printf("2. Listar Rotas\n");
  printf("3. Buscar Rota (Recursivo)\n");
  printf("4. Excluir Rota\n");
  printf("0. Voltar\n");
  read_validate_int("Escolha uma opcao: ", &option, 0, 4);
  return option;
}

unsigned int reports_menu(void) {
  unsigned int option;
  clear_terminal();
  printf("\n=== Relatorios e Exportacao ===\n");
  printf("1. Relatorios Avancados\n");
  printf("2. Exportar Dados (CSV/HTML)\n");
  printf("0. Voltar\n");
  read_validate_int("Escolha uma opcao: ", &option, 0, 2);
  return option;
}