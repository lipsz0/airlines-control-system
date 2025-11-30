#include "../include/register.h"
#include "../include/utils.h"
#include "../include/validation.h"

// Function to initialize the database of aircrafts
void init_db_aircraft (db_aircraft_t *db_aircraft) {
    db_aircraft->count = 0;
    db_aircraft->start = NULL;
    db_aircraft->end = NULL;
}

// Function to initialize the database of routes
void init_db_routes (db_routes_t *db_routes) {
    db_routes->count = 0;
    db_routes->start = NULL;
    db_routes->end = NULL;
}

// Function to insert an aircraft in the database
void register_aircraft (db_aircraft_t *db_aircraft, aircraft_t *aircraft, unsigned int mode) {
    if (db_aircraft->start == NULL) {
        db_aircraft->count++;
        db_aircraft->end = aircraft;
        db_aircraft->start = aircraft;
    }

    // 1. Insert at the start
    // 2. Insert at the end
    if (mode == 1) {
        aircraft->next = db_aircraft->start;
        db_aircraft->start = aircraft;
        db_aircraft->count++;
    } else if (mode == 2) {
        db_aircraft->end->next = aircraft;
        db_aircraft->end = aircraft;
        db_aircraft->count++;
    }
}

// Function to insert a route in the database
void register_route (db_routes_t *db_routes, routes_t *route, unsigned int mode) {
    if (db_routes->start == NULL) {
        db_routes->count++;
        db_routes->end = route;
        db_routes->start = route;
    }

    // 1. Insert at the start
    // 2. Insert at the end
    if (mode == 1) {
        route->next = db_routes->start;
        db_routes->start = route;
        db_routes->count++;
    } else if (mode == 2) {
        db_routes->end->next = route;
        db_routes->end = route;
        db_routes->count++;
    }
}

// Function to register a new aircraft
aircraft_t *new_aircraft (unsigned int *id) {
    aircraft_t *new_aircraft = (aircraft_t *) malloc (sizeof (aircraft_t));
    new_aircraft->id = *id + 1;
    id += 1;

    printf ("Aeronave ID: %d\n", new_aircraft->id);
    read_validate_string ("Modelo: ", new_aircraft->model, STR_LEN);
    read_validate_string ("Fabricante: ", new_aircraft->manufacturer, STR_LEN);
    read_validate_string ("Matricula: ", new_aircraft->prefix, PREFIX_LEN);
    read_validate_int ("Ano de fabricacao: ", &new_aircraft->fabrication_year, MIN_FAB_YEAR, get_current_year ());
    strcpy (new_aircraft->type, get_aircraft_type ("Tipo de aeronave\n(1 - Passageiros, 2 - Carga)\nEscolha uma opcao: "));
    read_validate_int ("Capacidade de passageiros: ", &new_aircraft->max_passengers, 1, 900);
    strcpy (new_aircraft->status, get_aircraft_status ("Status da aeronave\n(1 - Em operacao, 2 - Em manutencao, 3 - Fora de operacao)\nEscolha uma opcao: "));
    read_validate_int ("Tripulacao necessaria: ", &new_aircraft->required_crew, 1, 50);
    new_aircraft->maintenance_count = 0;

    new_aircraft->next = NULL;
    return new_aircraft;
}

// Function to register a new route
routes_t *new_route (unsigned int *id, db_aircraft_t *db_aircraft) {
    routes_t *new_route = (routes_t *) malloc (sizeof (routes_t));
    new_route->id = *id + 1;
    id += 1;

    printf ("Rota ID: %d\n", new_route->id);
    new_route->alloc_aircraft_id = search_aircraft_id ("ID da Aeronave a ser alocada: ", db_aircraft);
    read_validate_string ("Origem: ", new_route->origin, STR_LEN);
    read_validate_string ("Destino: ", new_route->destination, STR_LEN);
    read_validate_datetime ("Data e hora (DD/MM/YYYY HHh:MM): ", &new_route->datetime);
    read_validate_int ("Tempo estimado do voo (em horas): ", &new_route->flight_time.hour, 1, 24);
    read_validate_float ("Combutivel necessario (em litros): ", &new_route->required_fuel, 1, 320000);
    validate_passengers ("Quantidade de passageiros: ", &new_route->passengers_on_flight, db_aircraft, new_route->alloc_aircraft_id);
    read_validate_float ("Peso util (em Kg): ", &new_route->useful_weight, 1, 200000);
    read_validate_int ("Quantidade de tripulantes (máx. 50): ", &new_route->crew_members.members_count, 1, 50);
    for (int i = 0; i < new_route->crew_members.members_count; i++) {
        read_validate_string ("Nome do tripulante: ", new_route->crew_members.name, STR_LEN);
    }

    new_route->next = NULL;
    return new_route;
}