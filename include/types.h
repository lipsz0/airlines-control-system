#ifndef TYPES_H
#define TYPES_H

#define STR_SIZE 100
#define PREFIX_LEN 8

typedef char string_t[STR_SIZE];

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} datetime_t;

typedef struct crew {
    string_t name;
    int members_count;
} crew_t;

typedef struct aircraft {
    int id;
    string_t model;
    string_t manufacturer;
    char prefix[PREFIX_LEN];
    int fabrication_year;
    int type;
    int passengers;
    int status;
    int required_crew;
    int maintenance_count;
} aircraft_t;

typedef struct routes {
    int code;
    datetime_t datetime;
    string_t origin;
    string_t destination;
    int estimated_flight_time;
    float required_fuel;
    int passengers_on_flight;
    float useful_load;
    crew_t crew_members;
    int allocated_aircraft_id;
} routes_t;

#endif