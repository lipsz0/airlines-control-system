#ifndef MENU_H
#define MENU_H

#include "types.h"
#include "utils.h"

// Exibe o menu principal e retorna a opcao escolhida
unsigned int main_menu(void);

// Submenus
unsigned int aircraft_menu(void);
unsigned int routes_menu(void);
unsigned int reports_menu(void);

#endif