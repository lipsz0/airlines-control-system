#include "../include/search.h"
#include <stddef.h>

// Busca aeronave (recursivo)
// Retorna ponteiro ou NULL
aircraft_t *search_aircraft_recursive(aircraft_t *current, unsigned int id) {
  // Fim da lista
  if (current == NULL) {
    return NULL;
  }

  // Encontrou
  if (current->id == id) {
    return current;
  }

  // Busca no proximo
  return search_aircraft_recursive(current->next, id);
}

// Busca rota (recursivo)
// Retorna ponteiro ou NULL
routes_t *search_route_recursive(routes_t *current, unsigned int id) {
  // Fim da lista
  if (current == NULL) {
    return NULL;
  }

  // Encontrou
  if (current->id == id) {
    return current;
  }

  // Busca no proximo
  return search_route_recursive(current->next, id);
}
