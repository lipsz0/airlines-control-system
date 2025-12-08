#include "../include/export.h"
#include "../include/validation.h"

// Exporta aeronaves para CSV
void export_aircraft_to_csv(db_aircraft_t *db_aircraft) {
  char filename[STR_LEN];
  char filepath[STR_LEN * 2];

  read_validate_string("Digite o nome do arquivo (sem extensao): ", filename,
                       STR_LEN);
  to_lower_format(filename);

  snprintf(filepath, sizeof(filepath), "data/%s.csv", filename);

  FILE *file = fopen(filepath, "w");
  if (!file) {
    printf("Erro ao criar arquivo %s\n", filepath);
    return;
  }

  fprintf(file, "ID,Modelo,Fabricante,Matricula,Ano,Tipo,Passageiros,Status,"
                "Tripulacao,Manutencoes\n");

  aircraft_t *current = db_aircraft->start;
  while (current) {
    fprintf(file, "%d,%s,%s,%s,%d,%s,%d,%s,%d,%d\n", current->id,
            current->model, current->manufacturer, current->prefix,
            current->fabrication_year, current->type, current->max_passengers,
            current->status, current->required_crew,
            current->maintenance_count);
    current = current->next;
  }

  fclose(file);
  printf("Arquivo %s exportado com sucesso!\n", filepath);
}

// Exporta rotas para CSV
void export_routes_to_csv(db_routes_t *db_routes) {
  char filename[STR_LEN];
  char filepath[STR_LEN * 2];

  read_validate_string("Digite o nome do arquivo (sem extensao): ", filename,
                       STR_LEN);
  to_lower_format(filename);

  snprintf(filepath, sizeof(filepath), "data/%s.csv", filename);

  FILE *file = fopen(filepath, "w");
  if (!file) {
    printf("Erro ao criar arquivo %s\n", filepath);
    return;
  }

  fprintf(file, "ID,Origem,Destino,Data,Hora,Aeronave,Combustivel,Passageiros,"
                "PesoUtil\n");

  routes_t *current = db_routes->start;
  while (current) {
    fprintf(file, "%d,%s,%s,%02d/%02d/%d,%02d:%02d,%s (ID: %d),%.2f,%d,%.2f\n",
            current->id, current->origin, current->destination,
            current->datetime.day, current->datetime.month,
            current->datetime.year, current->datetime.hour,
            current->datetime.minute, current->alloc_aircraft->model,
            current->alloc_aircraft->id, current->required_fuel,
            current->passengers_on_flight, current->useful_weight);
    current = current->next;
  }

  fclose(file);
  printf("Arquivo %s exportado com sucesso!\n", filepath);
}

// Exporta tudo para HTML
void export_data_to_html(db_aircraft_t *db_aircraft, db_routes_t *db_routes) {
  char filename[STR_LEN];
  char filepath[STR_LEN * 2];

  read_validate_string("Digite o nome do arquivo (sem extensao): ", filename,
                       STR_LEN);
  to_lower_format(filename);

  snprintf(filepath, sizeof(filepath), "data/%s.html", filename);

  FILE *file = fopen(filepath, "w");
  if (!file) {
    printf("Erro ao criar arquivo %s\n", filepath);
    return;
  }

  fprintf(file, "<!DOCTYPE html><html><head><title>Relatorio Airlines Control "
                "System</title>");
  fprintf(
      file,
      "<style>body { font-family: Arial, sans-serif; } table {border-collapse: "
      "collapse; width: 100%%;} th, td {border: "
      "1px solid #ddd; padding: 8px;} tr:nth-child(even){background-color: "
      "#f2f2f2;} th {padding-top: 12px; padding-bottom: 12px; text-align: "
      "left; background-color: #000000; color: white;}</style>");
  fprintf(file, "</head><body>");

  fprintf(file, "<h1>Relatorio de Aeronaves</h1>");
  fprintf(file, "<table><tr><th>ID</th><th>Modelo</th><th>Fabricante</"
                "th><th>Matricula</th><th>Status</th></tr>");

  aircraft_t *current_aircraft = db_aircraft->start;
  while (current_aircraft) {
    fprintf(file,
            "<tr><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>",
            current_aircraft->id, current_aircraft->model,
            current_aircraft->manufacturer, current_aircraft->prefix,
            current_aircraft->status);
    current_aircraft = current_aircraft->next;
  }
  fprintf(file, "</table>");

  fprintf(file, "<h1>Relatorio de Rotas</h1>");
  fprintf(file, "<table><tr><th>ID</th><th>Origem</th><th>Destino</"
                "th><th>Data</th><th>Aeronave</th></tr>");

  routes_t *current_route = db_routes->start;
  while (current_route) {
    fprintf(file,
            "<tr><td>%d</td><td>%s</td><td>%s</td><td>%02d/%02d/%d "
            "%02d:%02d</td><td>%s</td></tr>",
            current_route->id, current_route->origin,
            current_route->destination, current_route->datetime.day,
            current_route->datetime.month, current_route->datetime.year,
            current_route->datetime.hour, current_route->datetime.minute,
            current_route->alloc_aircraft->model);
    current_route = current_route->next;
  }
  fprintf(file, "</table>");

  fprintf(file, "</body></html>");
  fclose(file);
  printf("Arquivo %s exportado com sucesso!\n", filepath);

  // Abre arquivo automaticamente (Linux)
  char command[STR_LEN * 3];
  snprintf(command, sizeof(command), "xdg-open %s > /dev/null 2>&1", filepath);
  system(command);
}
