#include "include/archives.h"
#include "include/export.h"
#include "include/menu.h"
#include "include/register.h"
#include "include/reports.h"
#include "include/search.h"
#include "include/types.h"
#include "include/utils.h"

int main(void) {
  srand(time(NULL));
  int main_option;
  unsigned int sub_option;
  unsigned int search_id;

  // Listas de aeronaves e rotas
  db_aircraft_t db_aircraft;
  db_routes_t db_routes;

  // Inicializa listas
  init_db_aircraft(&db_aircraft);
  init_db_routes(&db_routes);

  // Carrega dados do disco
  load_aircraft_from_file(&db_aircraft);
  load_routes_from_file(&db_routes, &db_aircraft);

  // Loop principal
  do {
    clear_terminal();
    main_option = main_menu();

    switch (main_option) {
    case 1: // Gerenciar Aeronaves
      do {
        sub_option = aircraft_menu();
        switch (sub_option) {
        case 1: // Cadastrar
          clear_terminal();
          aircraft_t *aircraft = new_aircraft(&db_aircraft);
          register_aircraft(&db_aircraft, aircraft, 2);
          wait_for_enter();
          break;
        case 2: // Listar
          clear_terminal();
          report_fleet(&db_aircraft);
          wait_for_enter();
          break;
        case 3: // Buscar
          clear_terminal();
          read_validate_int("Digite o ID da aeronave: ", &search_id, 0, 9999);
          aircraft_t *found_aircraft =
              search_aircraft_recursive(db_aircraft.start, search_id);
          if (found_aircraft) {
            printf("\nAeronave encontrada:\n");
            printf("Modelo: %s | Matricula: %s | Status: %s\n",
                   found_aircraft->model, found_aircraft->prefix,
                   found_aircraft->status);
          } else {
            printf("%s", ERROR_AIRCRAFT_NOT_FOUND);
          }
          wait_for_enter();
          break;
        case 4: // Manutencao
          clear_terminal();
          update_aircraft_status(&db_aircraft);
          wait_for_enter();
          break;
        case 5: // Excluir
          clear_terminal();
          delete_aircraft(&db_aircraft, &db_routes);
          wait_for_enter();
          break;
        case 0: // Voltar
          break;
        }
      } while (sub_option != 0);
      break;

    case 2: // Gerenciar Rotas
      do {
        sub_option = routes_menu();
        switch (sub_option) {
        case 1: // Cadastrar
          clear_terminal();
          routes_t *route = new_route(&db_routes, &db_aircraft);
          if (route != NULL) {
            register_route(&db_routes, route, 2);
          }
          wait_for_enter();
          break;
        case 2: // Listar
          clear_terminal();
          report_routes(&db_routes);
          wait_for_enter();
          break;
        case 3: // Buscar
          clear_terminal();
          read_validate_int("Digite o ID da rota: ", &search_id, 0, 9999);
          routes_t *found_route =
              search_route_recursive(db_routes.start, search_id);
          if (found_route) {
            printf("\nRota encontrada:\n");
            printf("Origem: %s -> Destino: %s | Data: %02d/%02d/%d\n",
                   found_route->origin, found_route->destination,
                   found_route->datetime.day, found_route->datetime.month,
                   found_route->datetime.year);
          } else {
            printf("Erro: Rota nao encontrada.\n");
          }
          wait_for_enter();
          break;
        case 4: // Excluir
          clear_terminal();
          delete_route(&db_routes);
          wait_for_enter();
          break;
        case 0: // Voltar
          break;
        }
      } while (sub_option != 0);
      break;

    case 3: // Relatorios e Exportacao
      do {
        sub_option = reports_menu();
        switch (sub_option) {
        case 1: // Relatorios Avancados
          clear_terminal();
          printf("=== Relatorios Avancados ===\n");
          printf("1. Porcentagem de voos por destino\n");
          printf("2. Porcentagem de voos por aeronave\n");
          printf("3. Consumo total de combustivel\n");
          printf("4. Historico de manutencoes\n");
          printf("0. Voltar\n");

          int report_opt;
          read_validate_int("Escolha uma opcao: ", (unsigned int *)&report_opt,
                            0, 4);

          if (report_opt == 0)
            break;

          clear_terminal();
          if (report_opt == 1)
            report_destination_percentage(&db_routes);
          else if (report_opt == 2)
            report_aircraft_flight_percentage(&db_routes, &db_aircraft);
          else if (report_opt == 3)
            report_total_fuel_consumption(&db_routes);
          else if (report_opt == 4)
            report_maintenance_count(&db_aircraft);

          wait_for_enter();
          break;
        case 2: // Exportar
          clear_terminal();
          printf("=== Exportar Dados ===\n");
          printf("1. Exportar Aeronaves (CSV)\n");
          printf("2. Exportar Rotas (CSV)\n");
          printf("3. Exportar Tudo (HTML)\n");
          printf("0. Voltar\n");

          int export_opt;
          read_validate_int("Escolha uma opcao: ", (unsigned int *)&export_opt,
                            0, 3);

          if (export_opt == 0)
            break;

          clear_terminal();
          if (export_opt == 1)
            export_aircraft_to_csv(&db_aircraft);
          else if (export_opt == 2)
            export_routes_to_csv(&db_routes);
          else if (export_opt == 3)
            export_data_to_html(&db_aircraft, &db_routes);

          wait_for_enter();
          break;
        case 0: // Voltar
          break;
        }
      } while (sub_option != 0);
      break;

    case 0:
      // Salva dados antes de sair
      clear_terminal();
      save_aircraft_to_file(&db_aircraft);
      save_routes_to_file(&db_routes);
      printf("Saindo do sistema...\n");
      break;

    default:
      clear_terminal();
      printf("Opcao invalida. Tente novamente.\n");
      wait_for_enter();
      break;
    }
  } while (main_option != 0);
  return 0;
}