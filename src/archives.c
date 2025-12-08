#include "../include/archives.h"
#include "../include/validation.h"

// Salva aeronaves em arquivo binario
void save_aircraft_to_file(db_aircraft_t *db_aircraft) {
  FILE *file = fopen("data/aircraft_data.bin", "wb");

  if (!file) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  // Percorre e salva
  aircraft_t *current = db_aircraft->start;
  while (current) {
    fwrite(current, sizeof(aircraft_t), 1, file);
    current = current->next;
  }

  fclose(file);
}

// Carrega aeronaves do arquivo
void load_aircraft_from_file(db_aircraft_t *db_aircraft) {
  FILE *file = fopen("data/aircraft_data.bin", "rb");
  aircraft_t *new_aircraft = NULL;

  if (!file) {
    printf("Erro ao abrir o arquivo de registro das aeronaves.\n");
    return;
  }

  // Le o arquivo ate o fim
  while (true) {
    new_aircraft = (aircraft_t *)malloc(sizeof(aircraft_t));
    // Para se falhar na leitura
    if (fread(new_aircraft, sizeof(aircraft_t), 1, file) != 1) {
      free(new_aircraft);
      break;
    }

    new_aircraft->next = NULL;
    // Adiciona na lista
    register_aircraft(db_aircraft, new_aircraft, 2);
  }

  fclose(file);
  printf("Aeronaves carregadas com sucesso.\n");
}

// Salva rotas em arquivo binario
void save_routes_to_file(db_routes_t *db_routes) {
  FILE *file = fopen("data/routes_data.bin", "wb");

  if (!file) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  routes_t *current = db_routes->start;
  while (current) {
    fwrite(current, sizeof(routes_t), 1, file);
    // Salva ID da aeronave para reconexao
    fwrite(&current->alloc_aircraft->id, sizeof(int), 1, file);
    current = current->next;
  }

  fclose(file);
}

// Carrega rotas do arquivo
void load_routes_from_file(db_routes_t *db_routes, db_aircraft_t *db_aircraft) {
  FILE *file = fopen("data/routes_data.bin", "rb");
  routes_t *new_route = NULL;
  unsigned int aircraft_id;

  if (!file) {
    printf("Erro ao abrir o arquivo de registro das rotas.\n");
    return;
  }

  // Le o arquivo ate o fim
  while (true) {
    new_route = (routes_t *)malloc(sizeof(routes_t));
    // Para se falhar na leitura
    if (fread(new_route, sizeof(routes_t), 1, file) != 1) {
      free(new_route);
      break;
    }

    // Le ID da aeronave
    if (fread(&aircraft_id, sizeof(int), 1, file) != 1) {
      free(new_route);
      break;
    }

    // Reconecta ponteiro da aeronave
    new_route->alloc_aircraft = validate_aircraft_id(aircraft_id, db_aircraft);

    // Se nao encontrar aeronave, mantem NULL
    if (new_route->alloc_aircraft == NULL) {
      // Poderia tratar erro aqui, mas por hora segue o fluxo
    }

    new_route->next = NULL;
    register_route(db_routes, new_route, 2);
  }

  fclose(file);
  printf("Rotas carregadas com sucesso.\n");
}