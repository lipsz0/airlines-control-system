#ifndef REPORTS_H
#define REPORTS_H

#include "types.h"
#include "utils.h"
#include "validation.h"

// Exibe relatorio de todas as aeronaves
void report_fleet(db_aircraft_t *db_aircraft);

// Exibe relatorio de todas as rotas
void report_routes(db_routes_t *db_routes);

// Relatorio: Porcentagem de voos para um destino em um periodo
void report_destination_percentage(db_routes_t *db_routes);

// Relatorio: Porcentagem de voos de uma aeronave
void report_aircraft_flight_percentage(db_routes_t *db_routes,
                                       db_aircraft_t *db_aircraft);

// Relatorio: Consumo total de combustivel em um periodo
void report_total_fuel_consumption(db_routes_t *db_routes);

// Relatorio: Quantidade de manutencoes por aeronave
void report_maintenance_count(db_aircraft_t *db_aircraft);

#endif