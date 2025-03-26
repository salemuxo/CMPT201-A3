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

Table* create_table(int size, ...)
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

Neighbourhood* create_neighbourhood(int id, char* name)
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