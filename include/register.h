#ifndef REGISTER_H
#define REGISTER_H

#include "types.h"

// Function to initialize the database of aircrafts
void init_db_aircraft (db_aircraft_t *db_aircraft);

// Function to initialize the database of routes
void init_db_routes (db_routes_t *db_routes);

// Function to insert an aircraft in the database
void register_aircraft (db_aircraft_t *db_aircraft, aircraft_t *aircraft, unsigned int mode);

// Function to insert a route in the database
void register_route (db_routes_t *db_routes, routes_t *route, unsigned int mode);

// Function to register a new aircraft
aircraft_t *new_aircraft (unsigned int *id);

// Function to register a new route
routes_t *new_route (unsigned int *id, db_aircraft_t *db_aircraft);

#endif