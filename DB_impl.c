/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Ardy RD
 */

#include "DB.h"      /* Import the public database header. */
#include <stdlib.h>
#include <string.h>

Table* create_table(char** values, int size)
{
    Table* create = malloc(sizeof(Table));

    create->values = values;
    create->size = size;

    return create;
}

void free_table(Table* table)
{
    free(table->values);
    free(table);
}

Neighbourhood* create_neighbourhood(int id, char* name)
{
    Neighbourhood* create = malloc(sizeof(Neighbourhood));

    create->id = id;

    create->name = malloc(strlen(name) + 1);
    strcpy(create->name, name);

    return create;
}

void free_neighbourhood(Neighbourhood* neighbourhood)
{
    free(neighbourhood->name);
    free(neighbourhood);
}

NeighbourhoodTable* create_neighbourhood_table(Neighbourhood* neighbourhoods, int size);

void free_neighbourhood_table(NeighbourhoodTable* table);