/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Salem, Berhan, Benjamin, Jonathan
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Ardy RD
 */

#include "DB.h"      /* Import the public database header. */
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

Table* create_table(unsigned int size, ...)
{
    // allocate memory for Table struct
    Table* create = malloc(sizeof(Table));
    if (create == NULL)
    {
        return NULL;
    }

    // allocate memory for values
    create->values = calloc(size, sizeof(char*));
    if (create->values == NULL)
    {
        free(create);
        return NULL;
    }

    // initialize variadic arguments
    va_list args;
    va_start(args, size);

    // loop through each slot in Table
    for (int i = 0; i < size; i++)
    {
        // store next arg in arg
        char* arg = va_arg(args, char*);
        
        // allocate memory for value
        create->values[i] = malloc(strlen(arg) + 1);
        if (create->values[i] == NULL)
        {
            for (int n = i - 1; n >= 0; n--)
            {
                free(create->values[n]);
            }
            free(create->values);
            free(create);
            va_end(args);
            return NULL;
        }

        // copy value into table
        strcpy(create->values[i], arg);
    }

    va_end(args);
    create->size = size;

    return create;
}

void free_table(Table* table)
{
    for (int i = 0; i < table->size; i++)
    {
        free(table->values[i]);
    }
    free(table->values);
    free(table);
}

char* lookup_by_id(Table* table, unsigned int id)
{
    if (table->size <= id) 
    {
        return NULL;
    }
    return table->values[id];
}

int lookup_by_value(Table* table, char* value)
{
    for (int i = 0; i < table->size; i++)
    {
        if (strcmp(table->values[i], value) == 0)
        {
            return i;
        }
    }

    return -1;
}

Neighbourhood* create_neighbourhood(unsigned int id, char* name)
{
    Neighbourhood* create = malloc(sizeof(Neighbourhood));
    if (create == NULL)
    {
        return NULL;
    }

    create->id = id;

    create->name = malloc(strlen(name) + 1);
    if (create->name == NULL)
    {
        free(create);
        return NULL;
    }
    strcpy(create->name, name);

    return create;
}

void free_neighbourhood(Neighbourhood* neighbourhood)
{
    free(neighbourhood->name);
    free(neighbourhood);
}

NeighbourhoodTable* create_neighbourhood_table(unsigned int capacity)
{
    NeighbourhoodTable* create = malloc(sizeof(NeighbourhoodTable));
    if (create == NULL)
    {
        return NULL;
    }

    create->neighbourhoods = calloc(capacity, sizeof(Neighbourhood*));

    create->size = 0;
    create->capacity = capacity;

    return create;
}

void free_neighbourhood_table(NeighbourhoodTable* table)
{
    for (int i = 0; i < table->size; i++)
    {
        free_neighbourhood(table->neighbourhoods[i]);
    }
    free(table->neighbourhoods);
    free(table);
}

void add_neighbourhood(NeighbourhoodTable* table, unsigned int id, char* name)
{
    Neighbourhood* neighbourhood = create_neighbourhood(id, name);

    table->neighbourhoods[table->size] = neighbourhood;
    table->size++;
}

char* get_neighbourhood_by_id(NeighbourhoodTable* table, unsigned int id)
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->neighbourhoods[i]->id == id)
        {
            return table->neighbourhoods[i]->name;
        }
    }

    return NULL;
}

int get_neighbourhood_by_name(NeighbourhoodTable* table, char* name)
{
    for (int i = 0; i < table->size; i++)
    {
        if (strcmp(table->neighbourhoods[i]->name, name) == 0)
        {
            return table->neighbourhoods[i]->id;
        }
    }

    return -1;
}