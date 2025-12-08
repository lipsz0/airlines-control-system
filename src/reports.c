#include "../include/reports.h"

// Relatorio de frota
void report_fleet(db_aircraft_t *db_aircraft) {
  aircraft_t *current_aircraft = db_aircraft->start;
  if (current_aircraft == NULL) {
    printf("%s", ERROR_EMPTY_DB);
    return;
  }
  // Itera e exibe
  while (current_aircraft) {
    printf("ID da aeronave................: %d\n", current_aircraft->id);
    printf("Modelo........................: %s\n", current_aircraft->model);
    printf("Fabricante....................: %s\n",
           current_aircraft->manufacturer);
    printf("Matricula.....................: %s\n", current_aircraft->prefix);
    printf("Ano de fabricacao.............: %d\n",
           current_aircraft->fabrication_year);
    printf("Tipo..........................: %s\n", current_aircraft->type);
    printf("Qtd maxima de passageiros.....: %d\n",
           current_aircraft->max_passengers);
    printf("Status........................: %s\n", current_aircraft->status);
    printf("Tripulacao necessaria.........: %d\n",
           current_aircraft->required_crew);
    printf("Qtd de manutencoes............: %d\n\n",
           current_aircraft->maintenance_count);
    current_aircraft = current_aircraft->next;
  }
  return;
}

// Relatorio de rotas
void report_routes(db_routes_t *db_routes) {
  routes_t *current_route = db_routes->start;
  if (current_route == NULL) {
    printf("%s", ERROR_EMPTY_DB);
    return;
  }
  // Itera e exibe
  while (current_route) {
    printf("ID da rota....................: %d\n", current_route->id);
    printf("Aeronave alocada..............: %s | id: %d\n",
           current_route->alloc_aircraft->model,
           current_route->alloc_aircraft->id);
    printf("Origem........................: %s\n", current_route->origin);
    printf("Destino.......................: %s\n", current_route->destination);
    printf("Data e hora...................: %d/%d/%d %d:%d\n",
           current_route->datetime.day, current_route->datetime.month,
           current_route->datetime.year, current_route->datetime.hour,
           current_route->datetime.minute);
    printf("Tempo de voo..................: %d horas\n",
           current_route->flight_time.hour);
    printf("Combustivel necessario........: %.2f (Litros)\n",
           current_route->required_fuel);
    printf("Qtd passageiros...............: %d\n",
           current_route->passengers_on_flight);
    printf("Peso util.....................: %.2f (Toneladas)\n",
           current_route->useful_weight);
    printf("Tripulacao....................: \n");
    for (int i = 0; i < current_route->crew_members.members_count; i++) {
      printf("Membro [%d]: %s, ", i, current_route->crew_members.name);
    }
    printf("\n\n");
    current_route = current_route->next;
  }
  return;
}

// Relatorio: % voos por destino
void report_destination_percentage(db_routes_t *db_routes) {
  if (db_routes->start == NULL) {
    printf("%s", ERROR_EMPTY_DB);
    return;
  }

  char destination[STR_LEN];
  datetime_t start_date, end_date;

  read_validate_string("Digite o destino: ", destination, STR_LEN);
  read_validate_datetime("Data inicial (dd/mm/aaaa): ", &start_date);
  read_validate_datetime("Data final (dd/mm/aaaa): ", &end_date);

  int total_flights = 0;
  int dest_flights = 0;

  routes_t *current = db_routes->start;
  while (current) {
    if (is_date_between(&current->datetime, &start_date, &end_date)) {
      total_flights++;
      if (strcmp(current->destination, destination) == 0) {
        dest_flights++;
      }
    }
    current = current->next;
  }

  if (total_flights == 0) {
    printf("\nNenhum voo encontrado no periodo informado.\n");
  } else {
    float percentage = ((float)dest_flights / total_flights) * 100;
    printf("\n--- Relatorio de Destino ---\n");
    printf("Destino: %s\n", destination);
    printf("Periodo: %02d/%02d/%d a %02d/%02d/%d\n", start_date.day,
           start_date.month, start_date.year, end_date.day, end_date.month,
           end_date.year);
    printf("Total de voos no periodo: %d\n", total_flights);
    printf("Voos para %s: %d\n", destination, dest_flights);
    printf("Porcentagem: %.2f%%\n", percentage);
  }
}

// Relatorio: % voos por aeronave
void report_aircraft_flight_percentage(db_routes_t *db_routes,
                                       db_aircraft_t *db_aircraft) {
  if (db_routes->start == NULL) {
    printf("%s", ERROR_EMPTY_DB);
    return;
  }

  unsigned int aircraft_id;
  read_validate_int("Digite o ID da aeronave: ", &aircraft_id, 0, 9999);

  aircraft_t *aircraft = validate_aircraft_id(aircraft_id, db_aircraft);
  if (!aircraft)
    return;

  int total_flights = 0;
  int aircraft_flights = 0;

  routes_t *current = db_routes->start;
  while (current) {
    total_flights++;
    if (current->alloc_aircraft->id == aircraft_id) {
      aircraft_flights++;
    }
    current = current->next;
  }

  if (total_flights == 0) {
    printf("\nNenhum voo registrado no sistema.\n");
  } else {
    float percentage = ((float)aircraft_flights / total_flights) * 100;
    printf("\n--- Relatorio de Aeronave ---\n");
    printf("Aeronave: %s (ID: %d)\n", aircraft->model, aircraft->id);
    printf("Total de voos do sistema: %d\n", total_flights);
    printf("Voos desta aeronave: %d\n", aircraft_flights);
    printf("Porcentagem: %.2f%%\n", percentage);
  }
}

// Relatorio: Consumo total de combustivel
void report_total_fuel_consumption(db_routes_t *db_routes) {
  if (db_routes->start == NULL) {
    printf("%s", ERROR_EMPTY_DB);
    return;
  }

  datetime_t start_date, end_date;
  read_validate_datetime("Data inicial (dd/mm/aaaa): ", &start_date);
  read_validate_datetime("Data final (dd/mm/aaaa): ", &end_date);

  float total_fuel = 0;
  int count = 0;

  routes_t *current = db_routes->start;
  while (current) {
    if (is_date_between(&current->datetime, &start_date, &end_date)) {
      total_fuel += current->required_fuel;
      count++;
    }
    current = current->next;
  }

  printf("\n--- Relatorio de Combustivel ---\n");
  printf("Periodo: %02d/%02d/%d a %02d/%02d/%d\n", start_date.day,
         start_date.month, start_date.year, end_date.day, end_date.month,
         end_date.year);
  printf("Voos considerados: %d\n", count);
  printf("Consumo total: %.2f Litros\n", total_fuel);
}

// Relatorio: Manutencoes por aeronave
void report_maintenance_count(db_aircraft_t *db_aircraft) {
  if (db_aircraft->start == NULL) {
    printf("%s", ERROR_EMPTY_DB);
    return;
  }

  printf("\n--- Relatorio de Manutencoes ---\n");
  aircraft_t *current = db_aircraft->start;
  while (current) {
    printf("ID: %d | Modelo: %s | Manutencoes: %d | Status: %s\n", current->id,
           current->model, current->maintenance_count, current->status);
    current = current->next;
  }
}