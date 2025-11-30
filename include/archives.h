#ifndef ARCHIVES_H
#define ARCHIVES_H

#include "types.h"
#include "utils.h"

// Function to save aircraft database to file
void save_aircraft_to_file (db_aircraft_t *db_aircraft);

// Function to load aircraft database from file
void load_aircraft_from_file (db_aircraft_t *db_aircraft);

// Function to save routes database to file
void save_routes_to_file (db_routes_t *db_routes);

// Function to load routes database from file
void load_routes_from_file (db_routes_t *db_routes);

#endif