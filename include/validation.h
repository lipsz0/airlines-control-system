#ifndef VALIDATION_H
#define VALIDATION_H

#include "types.h"
#include "utils.h"

// Le e valida inteiro
int read_validate_int(const char *instruction, unsigned int *dest,
                      unsigned int min, unsigned int max);

// Le e valida float
float read_validate_float(const char *instruction, float *dest, float min,
                          float max);

// Le e valida string
void read_validate_string(const char *instruction, char *dest, int max_length);

// Le e valida data e hora
void read_validate_datetime(const char *instruction, datetime_t *datetime);

// Verifica se data e valida
bool is_valid_datetime(datetime_t *datetime);

// Compara duas datas
int compare_datetime(datetime_t *dt1, datetime_t *dt2);

// Verifica se data esta no intervalo
bool is_date_between(datetime_t *dt_check, datetime_t *dt_start,
                     datetime_t *dt_end);

// Obtem tipo de aeronave
char *get_aircraft_type(const char *instruction);

// Obtem status da aeronave
char *get_aircraft_status(const char *instruction);

// Valida ID da aeronave
aircraft_t *validate_aircraft_id(unsigned int search_id,
                                 db_aircraft_t *db_aircraft);

// Valida quantidade de passageiros
unsigned int validate_passengers(const char *instruction, aircraft_t *aircraft,
                                 unsigned int *dest);

// Verifica se a matricula da aeronave e unica
bool is_unique_prefix(const char *prefix, db_aircraft_t *db_aircraft);

// Verifica se existe conflito de horario para a aeronave
bool check_route_overlap(db_routes_t *db_routes, unsigned int aircraft_id,
                         datetime_t *start_time, float duration_hours);

#endif