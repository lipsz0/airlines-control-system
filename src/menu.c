#include "../include/menu.h"

unsigned int main_menu (void) {
    unsigned int option;
    printf ("=== Sistema de Controle de Companhias Aereas ===\n");
    printf ("1. Registrar Aeronave\n");
    printf ("2. Registrar Rota\n");
    printf ("0. Sair\n");
    printf ("Escolha uma opcao: ");
    scanf ("%d", &option);
    clear_buffer ();
    return option;
}