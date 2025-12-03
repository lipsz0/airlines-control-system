#include "../include/search.h"
#include <stddef.h>

// Busca recursiva de aeronave por ID
// Retorna o ponteiro para a aeronave se encontrar, ou NULL se nao encontrar
aircraft_t *search_aircraft_recursive(aircraft_t *current, unsigned int id) {
  // Caso base 1: Chegou ao fim da lista sem encontrar
  if (current == NULL) {
    return NULL;
  }

  // Caso base 2: Encontrou o ID
  if (current->id == id) {
    return current;
  }

  // Passo recursivo: Continua buscando no proximo no
  return search_aircraft_recursive(current->next, id);
}

// Busca recursiva de rota por ID
// Retorna o ponteiro para a rota se encontrar, ou NULL se nao encontrar
routes_t *search_route_recursive(routes_t *current, unsigned int id) {
  // Caso base 1: Chegou ao fim da lista sem encontrar
  if (current == NULL) {
    return NULL;
  }

  // Caso base 2: Encontrou o ID
  if (current->id == id) {
    return current;
  }

  // Passo recursivo: Continua buscando no proximo no
  return search_route_recursive(current->next, id);
}
