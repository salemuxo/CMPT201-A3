#include <stdio.h>
#include "../DB.h"
#include "../DB_impl.h"

int main()
{
    NeighbourhoodTable* table = create_neighbourhood_table(10);

    add_neighbourhood(table, 10500, "N1");
    add_neighbourhood(table, 122335, "N2");
    add_neighbourhood(table, 1324, "N3");

    printf("ID: %d, Name: %s\n", get_neighbourhood_by_name(table, "N1"), get_neighbourhood_by_id(table, 10500));
    printf("ID: %d, Name: %s\n", get_neighbourhood_by_name(table, "N2"), get_neighbourhood_by_id(table, 122335));
    printf("ID: %d, Name: %s\n", get_neighbourhood_by_name(table, "N3"), get_neighbourhood_by_id(table, 1324));

    free_neighbourhood_table(table);

    return 0;
}