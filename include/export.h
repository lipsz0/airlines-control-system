#ifndef EXPORT_H
#define EXPORT_H

#include "types.h"
#include "utils.h"

// Exporta lista de aeronaves para CSV
void export_aircraft_to_csv(db_aircraft_t *db_aircraft);

// Exporta lista de rotas para CSV
void export_routes_to_csv(db_routes_t *db_routes);

// Exporta dados completos para HTML
void export_data_to_html(db_aircraft_t *db_aircraft, db_routes_t *db_routes);

#endif
