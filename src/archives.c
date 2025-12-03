#include "../include/archives.h"
#include "../include/validation.h"

// Salva a lista de aeronaves no arquivo binario
void save_aircraft_to_file(db_aircraft_t *db_aircraft) {
  FILE *file = fopen("data/aircraft_data.bin", "wb");

  if (!file) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  // Percorre a lista salvando cada estrutura
  aircraft_t *current = db_aircraft->start;
  while (current) {
    fwrite(current, sizeof(aircraft_t), 1, file);
    current = current->next;
  }

  fclose(file);
}

// Carrega a lista de aeronaves do arquivo binario
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
    // Se nao conseguir ler um item completo, para o loop
    if (fread(new_aircraft, sizeof(aircraft_t), 1, file) != 1) {
      free(new_aircraft);
      break;
    }

    new_aircraft->next = NULL;
    // Adiciona na lista em memoria
    register_aircraft(db_aircraft, new_aircraft, 2);
  }

  fclose(file);
  printf("Aeronaves carregadas com sucesso.\n");
}

// Salva a lista de rotas no arquivo binario
void save_routes_to_file(db_routes_t *db_routes) {
  FILE *file = fopen("data/routes_data.bin", "wb");

  if (!file) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  routes_t *current = db_routes->start;
  while (current) {
    fwrite(current, sizeof(routes_t), 1, file);
    // Salva o ID da aeronave separadamente para poder reconectar o ponteiro ao
    // carregar
    fwrite(&current->alloc_aircraft->id, sizeof(unsigned int), 1, file);
    current = current->next;
  }

  fclose(file);
}

// Carrega a lista de rotas do arquivo binario
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
    // Se nao conseguir ler um item completo, para o loop
    if (fread(new_route, sizeof(routes_t), 1, file) != 1) {
      free(new_route);
      break;
    }

    // Le o ID da aeronave associada
    if (fread(&aircraft_id, sizeof(unsigned int), 1, file) != 1) {
      free(new_route);
      break;
    }

    // Busca a aeronave na memoria pelo ID e reconecta o ponteiro
    new_route->alloc_aircraft = validate_aircraft_id(aircraft_id, db_aircraft);

    // Se a aeronave nao for encontrada (banco corrompido ou deletado), mantem
    // NULL
    if (new_route->alloc_aircraft == NULL) {
      // Poderia tratar erro aqui, mas por hora segue o fluxo
    }

    new_route->next = NULL;
    register_route(db_routes, new_route, 2);
  }

  fclose(file);
  printf("Rotas carregadas com sucesso.\n");
}