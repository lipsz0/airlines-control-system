#include "../include/validation.h"

int read_validate_int (const char *instruction, unsigned int *dest, unsigned int min, unsigned int max) {
    while (true) {
        printf ("%s", instruction);
        if (scanf ("%d", dest) != 1) {
             clear_buffer();
             printf ("%s", ERROR_INVALID_INPUT);
             continue;
        }
        clear_buffer ();
        if (*dest < min || *dest > max) {
            printf ("%s", ERROR_OUT_OF_RANGE);
            continue;
        }
        break;
    }
    return 0;
}

float read_validate_float (const char *instruction, float *dest, float min, float max) {
    while (true) {
        printf ("%s", instruction);
        if (scanf ("%f", dest) != 1) {
             clear_buffer();
             printf ("%s", ERROR_INVALID_INPUT);
             continue;
        }
        clear_buffer ();
        if (*dest < min || *dest > max) {
            printf ("%s", ERROR_OUT_OF_RANGE);
            continue;
        }
        break;
    }
    return 0;
}

void read_validate_string (const char *intruction, char *dest, int max_length) {
    while (true) {
        printf ("%s", intruction);
        fgets (dest, max_length, stdin);
        if (*(dest) == '\n' || *(dest) == ' ' || *(dest) == '\0') {
            printf ("%s", ERROR_INVALID_INPUT);
            return;
        }
        retire_newline (dest);
        tolower_format (dest);
        break;
    }
}

void read_validate_datetime (const char *instruction, datetime_t *datetime) {
    while (true) {
        sscanf (instruction, "%04d/%02d/%02d %02d:%02d", &datetime->year, &datetime->month, &datetime->day, &datetime->hour, &datetime->minute);
        if (!is_valid_datetime (datetime)) {
            printf ("%s", ERROR_INVALID_DATE);
            return;
        }
        break;
    }
}

bool is_valid_datetime (datetime_t *datetime) {
    if (datetime->year < MIN_FAB_YEAR || datetime->year > get_current_year () || datetime->month < 1 || datetime->month > 12 || datetime->day < 1 || datetime->day > 31 || datetime->hour > 23 || datetime->minute > 59) {
        return false;
    }
    bool is_leap_year = (datetime->year % 4 == 0 && datetime->year % 100 != 0) || (datetime->year % 400 == 0);
    unsigned int dim = (datetime->month == 2) ? (is_leap_year ? 29 : 28) : ((datetime->month == 4 || datetime->month == 6 || datetime->month == 9 || datetime->month == 11) ? 30 : 31);
    return datetime->day <= dim;
}

int compare_datetime (datetime_t *dt1, datetime_t *dt2) {
    if (dt1->year != dt2->year) return dt1->year - dt2->year;
    if (dt1->month != dt2->month) return dt1->month - dt2->month;
    if (dt1->day != dt2->day) return dt1->day - dt2->day;
    if (dt1->hour != dt2->hour) return dt1->hour - dt2->hour;
    return dt1->minute - dt2->minute;
}

bool is_date_between (datetime_t *dt_check, datetime_t *dt_start, datetime_t *dt_end) { return compare_datetime (dt_check, dt_start) >= 0 && compare_datetime (dt_check, dt_end) <= 0; }

char *get_aircraft_type (const char *instruction) {
    unsigned int type;
    read_validate_int (instruction, &type, 1, 2);
    switch (type) {
        case 1:
            return "Passageiros";
        case 2:
            return "Carga";
        default:
            return NULL;
    }
}

char *get_aircraft_status (const char *instruction) {
    unsigned int status;
    read_validate_int (instruction, &status, 1, 3);
    switch (status) {
        case 1:
            return "Em operacao";
        case 2:
            return "Em manutencao";
        case 3:
            return "Fora de operacao";
        default:
            return NULL;
    }
}

unsigned int search_aircraft_id (const char *instruction, db_aircraft_t *db_aircraft) {
    printf ("%s", instruction);
    unsigned int search_id;
    if (scanf ("%d", &search_id) != 1) {
        clear_buffer();
        printf ("%s", ERROR_INVALID_INPUT);
        return 0;
    }
    clear_buffer ();
    aircraft_t *current = db_aircraft->start;
    while (current) {
        if (current->id == search_id) {
            if (strcmp(current->status, "Em operacao") != 0) {
                printf ("%s", ERROR_AIRCRAFT_UNDER_MAINTENANCE);
                return 0;
            } else {
                return search_id;
            }
        }
        current = current->next;
    }
    printf ("%s", ERROR_AIRCRAFT_NOT_FOUND);
    return 0;
}

unsigned int validate_passengers (const char *instruction, unsigned int *dest, db_aircraft_t *db_aircraft, unsigned int aircraft_id) {
    while (true) {
        printf ("%s", instruction);
        if (scanf ("%d", dest) != 1) {
            clear_buffer();
            printf ("%s", ERROR_INVALID_INPUT);
            continue;
        }
        clear_buffer();
        
        aircraft_t *current = db_aircraft->start;
        bool found = false;
        while (current) {
            if (current->id == aircraft_id) {
                found = true;
                if (*dest > current->max_passengers) {
                    printf ("%s", ERROR_EXCEEDS_CAPACITY);
                    break; 
                } else {
                    return current->max_passengers;
                }
            }
            current = current->next;
        }
        if (!found) {
            printf ("%s", ERROR_AIRCRAFT_NOT_FOUND);
            return 0;
        }
    }
    return 0;
}