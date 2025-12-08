#include "../include/register.h"

#include "../include/search.h"
#include "../include/utils.h"
#include "../include/validation.h"

// Zera a lista de aeronaves
void init_db_aircraft(db_aircraft_t *db_aircraft) {
  db_aircraft->count = 0;
  db_aircraft->start = db_aircraft->end = NULL;
}

// Zera a lista de rotas
void init_db_routes(db_routes_t *db_routes) {
  db_routes->count = 0;
  db_routes->start = db_routes->end = NULL;
}

// Cadastra aeronave na lista
void register_aircraft(db_aircraft_t *db_aircraft, aircraft_t *aircraft,
                       register_type_t mode) {
  // Lista vazia: insere no inicio
  if (db_aircraft->start == NULL) {
    db_aircraft->count++;
    db_aircraft->start = db_aircraft->end = aircraft;
    return;
  }

  // Insere conforme o modo (inicio ou fim)
  if (mode == REGISTER_AT_START) {
    aircraft->next = db_aircraft->start;
    db_aircraft->start = aircraft;
    db_aircraft->count++;
    return;
  } else if (mode == REGISTER_AT_END) {
    db_aircraft->end->next = aircraft;
    db_aircraft->end = aircraft;
    db_aircraft->count++;
    return;
  }
}

// Cadastra rota na lista
void register_route(db_routes_t *db_routes, routes_t *route,
                    register_type_t mode) {
  // Lista vazia: insere no inicio
  if (db_routes->start == NULL) {
    db_routes->count++;
    db_routes->start = db_routes->end = route;
    return;
  }

  // Insere conforme o modo
  if (mode == REGISTER_AT_START) {
    route->next = db_routes->start;
    db_routes->start = route;
    db_routes->count++;
    return;
  } else if (mode == 2) {
    db_routes->end->next = route;
    db_routes->end = route;
    db_routes->count++;
    return;
  }
}

// Cria nova aeronave com input do usuario
aircraft_t *new_aircraft(db_aircraft_t *db_aircraft) {
  aircraft_t *new_aircraft = (aircraft_t *)calloc(1, sizeof(aircraft_t));
  // ID automatico
  new_aircraft->id = db_aircraft->count + 1000;

  printf("Aeronave ID: %d\n", new_aircraft->id);
  read_validate_string("\nModelo: ", new_aircraft->model, STR_LEN);
  read_validate_string("\nFabricante: ", new_aircraft->manufacturer, STR_LEN);

  while (true) {
    read_validate_string("\nMatricula: ", new_aircraft->prefix, PREFIX_LEN);
    if (is_unique_prefix(new_aircraft->prefix, db_aircraft)) {
      break;
    }
    printf("%s", ERROR_DUPLICATE_PREFIX);
  }

  read_validate_int("\nAno de fabricacao: ", &new_aircraft->fabrication_year,
                    MIN_FAB_YEAR, get_current_year());
  strcpy(new_aircraft->type,
         get_aircraft_type("\nTipo de aeronave:\n1. Passageiros\n2. "
                           "Carga\nEscolha uma opcao: "));

  // Capacidade apenas para passageiros
  if (strcmp(new_aircraft->type, "Passageiros") == 0) {
    read_validate_int(
        "\nCapacidade de passageiros: ", &new_aircraft->max_passengers, 1, 900);
  } else {
    new_aircraft->max_passengers = 0;
  }

  strcpy(
      new_aircraft->status,
      get_aircraft_status(
          "\nStatus da aeronave\n1. Em operacao\n2. Em manutencao\n3. Fora de "
          "operacao\nEscolha uma opcao: "));
  read_validate_int("\nTripulacao necessaria: ", &new_aircraft->required_crew,
                    1, 50);
  new_aircraft->maintenance_count = 0;

  new_aircraft->next = NULL;
  clear_terminal();
  printf("\nAeronave [ID %d] registrada com sucesso!\n\n", new_aircraft->id);
  return new_aircraft;
}

// Cria nova rota com input do usuario
routes_t *new_route(db_routes_t *db_routes, db_aircraft_t *db_aircraft) {
  routes_t *new_route = (routes_t *)calloc(1, sizeof(routes_t));
  // ID automatico
  new_route->id = db_routes->count + 3000;

  printf("\nRota ID: %d\n", new_route->id);

  // Garante aeronave valida
  while (new_route->alloc_aircraft == NULL) {
    unsigned int temp_id;
    read_validate_int("\nID da Aeronave a ser alocada: ", &temp_id, 0, 9999);
    new_route->alloc_aircraft = validate_aircraft_id(temp_id, db_aircraft);
  }

  while (true) {
    read_validate_string("\nOrigem: ", new_route->origin, STR_LEN);
    read_validate_string("\nDestino: ", new_route->destination, STR_LEN);
    if (strcmp(new_route->origin, new_route->destination) != 0) {
      break;
    }
    printf("%s", ERROR_SAME_ORIGIN_DEST);
  }

  while (true) {
    read_validate_datetime("\nData e hora (dd/mm/aaaa hh:mm): ",
                           &new_route->datetime);
    if (new_route->datetime.year >=
        new_route->alloc_aircraft->fabrication_year) {
      break;
    }
    printf(ERROR_INVALID_ROUTE_DATE,
           new_route->alloc_aircraft->fabrication_year);
  }

  read_validate_int("\nTempo estimado do voo (em horas): ",
                    &new_route->flight_time.hour, 1, 24);

  // Verifica conflito de horario
  if (check_route_overlap(db_routes, new_route->alloc_aircraft->id,
                          &new_route->datetime,
                          (float)new_route->flight_time.hour)) {
    printf("%s", ERROR_ROUTE_OVERLAP);
    printf("%s", ERROR_ROUTE_CANCELLED);
    free(new_route);
    return NULL; // Retorna NULL para indicar falha no cadastro
  }

  read_validate_float("\nCombutivel necessario (em litros): ",
                      &new_route->required_fuel, 1, 320000);

  // Valida passageiros vs capacidade
  validate_passengers(
      "\nQuantidade de passageiros: ", new_route->alloc_aircraft,
      &new_route->passengers_on_flight);

  read_validate_float("\nPeso util (em Kg): ", &new_route->useful_weight, 1,
                      250000);

  // Valida tripulacao minima
  while (true) {
    read_validate_int("\nQuantidade de tripulantes (máx. 50): ",
                      &new_route->crew_members.members_count, 1, 50);
    if (new_route->crew_members.members_count >=
        new_route->alloc_aircraft->required_crew) {
      break;
    }
    printf(ERROR_INSUFFICIENT_CREW, new_route->alloc_aircraft->required_crew);
  }

  for (int i = 0; i < new_route->crew_members.members_count; i++) {
    read_validate_string("\nNome do tripulante: ", new_route->crew_members.name,
                         STR_LEN);
  }

  new_route->next = NULL;
  clear_terminal();
  printf("\nRota [ID %d] registrada com sucesso!\n", new_route->id);
  return new_route;
}

// Atualiza status da aeronave
void update_aircraft_status(db_aircraft_t *db_aircraft) {
  unsigned int id;
  read_validate_int("Digite o ID da aeronave para alterar o status: ", &id, 0,
                    9999);

  aircraft_t *current = search_aircraft_recursive(db_aircraft->start, id);

  if (current) {
    printf("\nAeronave encontrada: %s (Status atual: %s)\n", current->model,
           current->status);
    printf("Deseja alterar o status?\n");
    printf("1. Colocar em Manutencao\n");
    printf("2. Colocar em Operacao\n");
    printf("3. Retirar de Operacao (Inativo)\n");
    printf("0. Cancelar\n");

    unsigned int op;
    read_validate_int("Opcao: ", &op, 0, 3);

    if (op == 0)
      return;

    if (op == 1) {
      if (strcmp(current->status, "Em manutencao") == 0) {
        printf("\nAeronave ja esta em manutencao.\n");
      } else {
        strcpy(current->status, "Em manutencao");
        current->maintenance_count++;
        printf("\nStatus alterado para 'Em manutencao'. Contador de "
               "manutencao incrementado.\n");
      }
    } else if (op == 2) {
      strcpy(current->status, "Em operacao");
      printf("\nStatus alterado para 'Em operacao'.\n");
    } else if (op == 3) {
      strcpy(current->status, "Fora de operacao");
      printf("\nStatus alterado para 'Fora de operacao'.\n");
    }
    return;
  }
  printf("%s", ERROR_AIRCRAFT_NOT_FOUND);
}

// Remove aeronave da lista
void delete_aircraft(db_aircraft_t *db_aircraft, db_routes_t *db_routes) {
  unsigned int id;
  read_validate_int("Digite o ID da aeronave a ser excluida: ", &id, 0, 9999);

  aircraft_t *current = db_aircraft->start;
  aircraft_t *previous = NULL;

  while (current != NULL) {
    if (current->id == id) {
      // Verifica se esta em uso
      routes_t *route_current = db_routes->start;
      while (route_current != NULL) {
        if (route_current->alloc_aircraft->id == id) {
          printf(
              "Erro: Nao e possivel excluir a aeronave [ID %d] pois ela esta "
              "alocada na rota [ID %d].\n",
              id, route_current->id);
          return;
        }
        route_current = route_current->next;
      }

      // Remove da lista
      if (previous == NULL) {
        db_aircraft->start = current->next;
      } else {
        previous->next = current->next;
      }

      if (current == db_aircraft->end) {
        db_aircraft->end = previous;
      }

      free(current);
      db_aircraft->count--;
      printf("Aeronave [ID %d] excluida com sucesso.\n", id);
      return;
    }
    previous = current;
    current = current->next;
  }

  printf("%s", ERROR_AIRCRAFT_NOT_FOUND);
}

// Remove rota da lista
void delete_route(db_routes_t *db_routes) {
  unsigned int id;
  read_validate_int("Digite o ID da rota a ser excluida: ", &id, 0, 9999);

  routes_t *current = db_routes->start;
  routes_t *previous = NULL;

  while (current != NULL) {
    if (current->id == id) {
      // Remove da lista
      if (previous == NULL) {
        db_routes->start = current->next;
      } else {
        previous->next = current->next;
      }

      if (current == db_routes->end) {
        db_routes->end = previous;
      }

      free(current);
      db_routes->count--;
      printf("Rota [ID %d] excluida com sucesso.\n", id);
      return;
    }
    previous = current;
    current = current->next;
  }

  printf("Erro: Rota nao encontrada.\n");
}
