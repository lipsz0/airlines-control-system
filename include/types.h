#ifndef TYPES_H
#define TYPES_H

#define STR_LEN 100
#define PREFIX_LEN 8
#define MIN_FAB_YEAR 1970
#define CURRENT_YEAR 2025

#define ERROR_INVALID_INPUT "Erro: Entrada invalida, tente novamente.\n"
#define ERROR_OUT_OF_RANGE "Erro: Valor fora do intervalo permitido, tente novamente.\n"
#define ERROR_INVALID_DATE "Erro: Data e hora invalida, tente novamente.\n"
#define ERROR_AIRCRAFT_NOT_FOUND "Erro: Aeronave nao encontrada, tente novamente.\n"
#define ERROR_EXCEEDS_CAPACITY "Erro: Quantidade de passageiros excede a capacidade da aeronave, tente novamente.\n"
#define ERROR_AIRCRAFT_UNDER_MAINTENANCE "Erro: Aeronave esta em manutencao e nao pode ser alocada, tente novamente.\n"

typedef char string_t[STR_LEN];

typedef struct {
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
} datetime_t;

typedef struct crew {
    string_t name;
    unsigned int members_count;
} crew_t;

typedef struct aircraft {
    unsigned int id;
    string_t model;
    string_t manufacturer;
    char prefix[PREFIX_LEN];
    unsigned int fabrication_year;
    string_t type;
    unsigned int max_passengers;
    string_t status;
    unsigned int required_crew;
    unsigned int maintenance_count;
    struct aircraft *next;
} aircraft_t;

typedef struct routes {
    unsigned int id;
    string_t origin;
    string_t destination;
    datetime_t datetime;
    datetime_t flight_time;
    float required_fuel;
    unsigned int passengers_on_flight;
    float useful_weight;
    crew_t crew_members;
    unsigned int alloc_aircraft_id;
    struct routes *next;
} routes_t;

typedef struct db_aircraft {
    unsigned int count;
    aircraft_t *start;
    aircraft_t *end;
} db_aircraft_t;

typedef struct db_routes {
    unsigned int count;
    routes_t *start;
    routes_t *end;
} db_routes_t;

#endif