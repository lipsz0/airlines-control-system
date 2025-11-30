#ifndef VALIDATION_H
#define VALIDATION_H

#include "types.h"
#include "utils.h"



int read_validate_int (const char *instruction, unsigned int *dest, unsigned int min, unsigned int max);
float read_validate_float (const char *instruction, float *dest, float min, float max);
void read_validate_string (const char *intruction, char *dest, int max_length);
void read_validate_datetime (const char *instruction, datetime_t *datetime);
bool is_valid_datetime (datetime_t *datetime);
int compare_datetime (datetime_t *dt1, datetime_t *dt2);
bool is_date_between (datetime_t *dt_check, datetime_t *dt_start, datetime_t *dt_end);
char *get_aircraft_type (const char *instruction);
char *get_aircraft_status (const char *instruction);
unsigned int search_aircraft_id (const char *instruction, db_aircraft_t *db_aircraft);
unsigned int validate_passengers (const char *instruction, unsigned int *dest, db_aircraft_t *db_aircraft, unsigned int aircraft_id);

#endif