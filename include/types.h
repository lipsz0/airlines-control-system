#ifndef TYPES_H
#define TYPES_H

// Constantes globais
#define STR_LEN 96
#define PREFIX_LEN 8
#define MIN_FAB_YEAR 1970

// Mensagens de erro padronizadas
#define FATAL_ERROR "Erro FATAL: Encerrando o programa.\n"
#define ERROR_EMPTY_DB                                                         \
  "Erro: Nenhum dado cadastrado. Por favor, realize o cadastro no sistema.\n"
#define ERROR_INVALID_INPUT                                                    \
  "Erro: Entrada invalida, por favor tente novamente.\n"
#define ERROR_OUT_OF_RANGE                                                     \
  "Erro: Valor fora do intervalo permitido, por favor tente novamente.\n"
#define ERROR_INVALID_DATE                                                     \
  "Erro: Data e hora invalida, por favor tente novamente.\n"
#define ERROR_AIRCRAFT_NOT_FOUND                                               \
  "Erro: Aeronave nao encontrada, por favor tente novamente.\n"
#define ERROR_EXCEEDS_CAPACITY                                                 \
  "Erro: Quantidade de passageiros acima da capacidade. Por favor, informe "   \
  "um valor menor.\n"
#define ERROR_AIRCRAFT_UNDER_MAINTENANCE                                       \
  "Erro: Esta aeronave esta em manutencao e nao pode ser alocada.\n"
#define ERROR_DUPLICATE_PREFIX                                                 \
  "Erro: Matricula ja cadastrada. Por favor, informe uma matricula unica.\n"
#define ERROR_SAME_ORIGIN_DEST                                                 \
  "Erro: Origem e destino sao iguais. Por favor, insira os locais novamente\n"
#define ERROR_INVALID_ROUTE_DATE                                               \
  "Erro: A data nao pode ser anterior ao ano de fabricacao da aeronave "       \
  "(%d).\n"
#define ERROR_ROUTE_OVERLAP                                                    \
  "Erro: Esta aeronave ja tem um voo agendado neste periodo.\n"
#define ERROR_ROUTE_CANCELLED                                                  \
  "Aviso: Cadastro de rota cancelado. Por favor, tente novamente.\n"
#define ERROR_INSUFFICIENT_CREW                                                \
  "Erro: Quantidade de tripulantes inferior ao minimo exigido pela aeronave "  \
  "(%d).\n"

// Tipo string padrao
typedef char string_t[STR_LEN];

// Enum para modo de registro (inicio ou fim da lista)
typedef enum register_type_t {
  REGISTER_AT_START = 1,
  REGISTER_AT_END = 2,
} register_type_t;

// Estrutura para data e hora
typedef struct {
  unsigned int year;
  unsigned int month;
  unsigned int day;
  unsigned int hour;
  unsigned int minute;
} datetime_t;

// Estrutura para tripulacao
typedef struct crew {
  string_t name;
  unsigned int members_count;
} crew_t;

// Estrutura para aeronave (no da lista encadeada)
typedef struct aircraft {
  unsigned int id;
  string_t model;
  string_t manufacturer;
  char prefix[PREFIX_LEN];
  unsigned int fabrication_year;
  string_t type;
  unsigned int max_passengers;
  string_t status;
  unsigned int required_crew;
  unsigned int maintenance_count;
  struct aircraft *next;
} aircraft_t;

// Estrutura para rota (no da lista encadeada)
typedef struct routes {
  unsigned int id;
  string_t origin;
  string_t destination;
  datetime_t datetime;
  datetime_t flight_time;
  float required_fuel;
  unsigned int passengers_on_flight;
  float useful_weight;
  crew_t crew_members;
  aircraft_t *alloc_aircraft;
  struct routes *next;
} routes_t;

// Estrutura de controle da lista de aeronaves
typedef struct db_aircraft {
  unsigned int count;
  aircraft_t *start;
  aircraft_t *end;
} db_aircraft_t;

// Estrutura de controle da lista de rotas
typedef struct db_routes {
  unsigned int count;
  routes_t *start;
  routes_t *end;
} db_routes_t;

#endif