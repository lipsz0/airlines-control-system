#include "include/archives.h"
#include "include/menu.h"
#include "include/register.h"
#include "include/types.h"
#include "include/utils.h"
#include "include/validation.h"

int main (void) {
    int main_option;
    int sub_option;

    // Databases
    db_aircraft_t db_aircraft;
    db_routes_t db_routes;

    // Initialize databases
    init_db_aircraft (&db_aircraft);
    init_db_routes (&db_routes);

    do {
        main_option = main_menu ();

        switch (main_option) {
            case 1:
                // Register Aircraft
                aircraft_t *aircraft = new_aircraft (&db_aircraft.count);
                register_aircraft (&db_aircraft, aircraft, 2);  // Insert at the end
                break;

            case 2:
                // Register Route
                routes_t *route = new_route (&db_routes.count, &db_aircraft);
                register_route (&db_routes, route, 2);  // Insert at the end
                break;

            case 0:
                // Exit
                printf ("Exiting the system. Goodbye!\n");
                break;

            default:
                printf ("Invalid option. Please try again.\n");
                break;
        }
    } while (main_option != 0);
    return 0;
}