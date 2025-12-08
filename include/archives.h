#ifndef ARCHIVES_H
#define ARCHIVES_H

#include "register.h"
#include "types.h"
#include "utils.h"

// Salva a lista de aeronaves no arquivo binario
void save_aircraft_to_file(db_aircraft_t *db_aircraft);

// Carrega a lista de aeronaves do arquivo binario para a memoria
void load_aircraft_from_file(db_aircraft_t *db_aircraft);

// Salva a lista de rotas no arquivo binario
void save_routes_to_file(db_routes_t *db_routes);

// Carrega a lista de rotas do arquivo binario para a memoria
void load_routes_from_file(db_routes_t *db_routes, db_aircraft_t *db_aircraft);

#endif