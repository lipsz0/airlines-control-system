#ifndef SEARCH_H
#define SEARCH_H

#include "types.h"

// Busca recursiva de aeronave por ID
aircraft_t *search_aircraft_recursive(aircraft_t *current, unsigned int id);

// Busca recursiva de rota por ID
routes_t *search_route_recursive(routes_t *current, unsigned int id);

#endif
