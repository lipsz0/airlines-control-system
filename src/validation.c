#include "../include/validation.h"

// Le e valida int
int read_validate_int(const char *instruction, unsigned int *dest,
                      unsigned int min, unsigned int max) {
  string_t temp;
  char *endptr;
  unsigned long value;

  while (true) {
    read_validate_string(instruction, temp, STR_LEN);
    value = strtoul(temp, &endptr, 10);
    // Verifica conversao
    if (*endptr != '\0' || temp == endptr) {
      printf("%s", ERROR_INVALID_INPUT);
      continue;
    }
    // Verifica intervalo
    if (value < min || value > max) {
      printf("%s", ERROR_OUT_OF_RANGE);
      continue;
    }
    return *dest = value;
  }
}

// Le e valida float
float read_validate_float(const char *instruction, float *dest, float min,
                          float max) {
  string_t temp;
  char *endptr;
  float value;

  while (true) {
    read_validate_string(instruction, temp, STR_LEN);
    value = strtof(temp, &endptr);
    // Verifica se a conversao foi bem sucedida
    if (*endptr != '\0' || temp == endptr) {
      printf("%s", ERROR_INVALID_INPUT);
      continue;
    }
    // Verifica se esta dentro do intervalo
    if (value < min || value > max) {
      printf("%s", ERROR_OUT_OF_RANGE);
      continue;
    }
    return *dest = value;
  }
}

// Le e valida string
void read_validate_string(const char *instruction, char *dest, int max_length) {
  char *ptr;
  while (true) {
    printf("%s", instruction);
    if (!fgets(dest, max_length, stdin)) {
      printf("%s", FATAL_ERROR);
      exit(1);
    }

    size_t len = strlen(dest);
    // Trata newline/buffer
    if (len && *(dest + len - 1) != '\n') {
      clear_buffer();
    } else {
      remove_newline(dest);
    }

    // Verifica espacos
    for (ptr = dest; *ptr && isspace(*ptr); ptr++)
      ;

    if (*ptr) {              // String valida
      to_upper_format(dest); // Normaliza
      return;
    }
    printf("%s", ERROR_INVALID_INPUT);
  }
}

// Le e valida datetime
void read_validate_datetime(const char *instruction, datetime_t *datetime) {
  string_t temp_input;
  unsigned int day, month, year, hour, minute;

  while (true) {
    printf("%s", instruction);
    if (fgets(temp_input, STR_LEN, stdin) != NULL) {
      // Formato completo
      if (sscanf(temp_input, "%d/%d/%d %d:%d", &day, &month, &year, &hour,
                 &minute) == 5) {
        datetime->day = day;
        datetime->month = month;
        datetime->year = year;
        datetime->hour = hour;
        datetime->minute = minute;
        if (is_valid_datetime(datetime)) {
          return;
        } else {
          printf("%s\n", ERROR_INVALID_DATE);
        }
      } else if (sscanf(temp_input, "%d/%d/%d", &day, &month, &year) == 3) {
        // Apenas data
        datetime->day = day;
        datetime->month = month;
        datetime->year = year;
        datetime->hour = 00;
        datetime->minute = 00;
        if (is_valid_datetime(datetime)) {
          return;
        } else {
          printf("%s\n", ERROR_INVALID_DATE);
        }
      } else {
        printf("%s\n", ERROR_INVALID_DATE);
      }
    } else {
      printf("%s", FATAL_ERROR);
      exit(1);
    }
  }
}

// Valida data (bissexto/dias)
bool is_valid_datetime(datetime_t *datetime) {
  if (datetime->year < MIN_FAB_YEAR || datetime->year > get_current_year() ||
      datetime->month < 1 || datetime->month > 12 || datetime->day < 1 ||
      datetime->day > 31 || datetime->hour > 23 || datetime->minute > 59) {
    return false;
  }
  bool is_leap_year = (datetime->year % 4 == 0 && datetime->year % 100 != 0) ||
                      (datetime->year % 400 == 0);
  unsigned int dim = (datetime->month == 2)
                         ? (is_leap_year ? 29 : 28)
                         : ((datetime->month == 4 || datetime->month == 6 ||
                             datetime->month == 9 || datetime->month == 11)
                                ? 30
                                : 31);
  return datetime->day <= dim;
}

// Compara datas
int compare_datetime(datetime_t *dt1, datetime_t *dt2) {
  if (dt1->year != dt2->year)
    return dt1->year - dt2->year;
  if (dt1->month != dt2->month)
    return dt1->month - dt2->month;
  if (dt1->day != dt2->day)
    return dt1->day - dt2->day;
  if (dt1->hour != dt2->hour)
    return dt1->hour - dt2->hour;
  return dt1->minute - dt2->minute;
}

// Verifica intervalo data
bool is_date_between(datetime_t *dt_check, datetime_t *dt_start,
                     datetime_t *dt_end) {
  return compare_datetime(dt_check, dt_start) >= 0 &&
         compare_datetime(dt_check, dt_end) <= 0;
}

// Obtem tipo aeronave
char *get_aircraft_type(const char *instruction) {
  unsigned int type;
  read_validate_int(instruction, &type, 1, 2);
  switch (type) {
  case 1:
    return "Passageiros";
  case 2:
    return "Carga";
  default:
    return NULL;
  }
}

// Obtem status
char *get_aircraft_status(const char *instruction) {
  unsigned int status;
  read_validate_int(instruction, &status, 1, 3);
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

// Valida ID aeronave
aircraft_t *validate_aircraft_id(unsigned int search_id,
                                 db_aircraft_t *db_aircraft) {
  aircraft_t *current_aircraft = db_aircraft->start;
  while (current_aircraft) {
    if (current_aircraft->id == search_id) {
      if (strcmp(current_aircraft->status, "Em manutencao") == 0) {
        printf("%s", ERROR_AIRCRAFT_UNDER_MAINTENANCE);
        return NULL;
      } else {
        return current_aircraft;
      }
    }
    current_aircraft = current_aircraft->next;
  }
  printf("%s", ERROR_AIRCRAFT_NOT_FOUND);
  return NULL;
}

// Valida passageiros
unsigned int validate_passengers(const char *instruction, aircraft_t *aircraft,
                                 unsigned int *dest) {
  if (strcmp(aircraft->type, "Carga") == 0) {
    return *dest = 0;
  } else {
    return read_validate_int(instruction, dest, 1, aircraft->max_passengers);
  }
}

// Valida matricula unica
bool is_unique_prefix(const char *prefix, db_aircraft_t *db_aircraft) {
  aircraft_t *current = db_aircraft->start;
  while (current) {
    if (strcmp(current->prefix, prefix) == 0) {
      return false;
    }
    current = current->next;
  }
  return true;
}

// Datetime para timestamp
time_t datetime_to_timestamp(datetime_t *dt) {
  struct tm tm_date;
  tm_date.tm_year = dt->year - 1900;
  tm_date.tm_mon = dt->month - 1;
  tm_date.tm_mday = dt->day;
  tm_date.tm_hour = dt->hour;
  tm_date.tm_min = dt->minute;
  tm_date.tm_sec = 0;
  return mktime(&tm_date);
}

// Verifica conflito
bool check_route_overlap(db_routes_t *db_routes, unsigned int aircraft_id,
                         datetime_t *start_time, float duration_hours) {

  time_t new_start = datetime_to_timestamp(start_time);
  time_t new_end = new_start + (time_t)(duration_hours * 3600);

  routes_t *current = db_routes->start;
  while (current) {
    if (current->alloc_aircraft->id == aircraft_id) {
      time_t current_start = datetime_to_timestamp(&current->datetime);
      // Calcula fim do voo existente
      float current_duration =
          current->flight_time.hour + (current->flight_time.minute / 60.0);
      time_t current_end = current_start + (time_t)(current_duration * 3600);

      // Se o novo começa antes do existente e termina depois do existente
      if (new_start < current_end && new_end > current_start) {
        return true; // Conflito encontrado
      }
    }
    current = current->next;
  }
  return false;
}