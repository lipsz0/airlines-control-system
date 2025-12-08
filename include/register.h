#ifndef REGISTER_H
#define REGISTER_H

#include "types.h"

// Inicializa a lista de aeronaves
void init_db_aircraft(db_aircraft_t *db_aircraft);

// Inicializa a lista de rotas
void init_db_routes(db_routes_t *db_routes);

// Insere uma aeronave na lista (inicio ou fim)
void register_aircraft(db_aircraft_t *db_aircraft, aircraft_t *aircraft,
                       register_type_t mode);

// Insere uma rota na lista (inicio ou fim)
void register_route(db_routes_t *db_routes, routes_t *route,
                    register_type_t mode);

// Cria uma nova aeronave solicitando dados ao usuario
aircraft_t *new_aircraft(db_aircraft_t *db_aircraft);

// Cria uma nova rota solicitando dados ao usuario
routes_t *new_route(db_routes_t *db_routes, db_aircraft_t *db_aircraft);

// Atualiza o status de uma aeronave (Operacao <-> Manutencao)
void update_aircraft_status(db_aircraft_t *db_aircraft);

// Remove uma aeronave da lista
void delete_aircraft(db_aircraft_t *db_aircraft, db_routes_t *db_routes);

// Remove uma rota da lista
void delete_route(db_routes_t *db_routes);

#endif