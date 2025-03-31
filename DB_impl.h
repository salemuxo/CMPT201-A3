/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: Salem, Berhan, Benjamin, Jonathan
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Ardy RD
 */


#include "DB.h"
#ifndef DB_IMPL_H
#define DB_IMPL_H

/*
Purpose: Creates a lookup table 

Parameters:
    unsigned int size: the number of elements in the lookup table
    char* ...: the strings to put in the lookup table

Returns: Table* - the pointer to the created table
*/
Table* create_table(unsigned int size, ...);

/*
Purpose: Frees memory associated with a lookup table

Parameters:
    Table* table: the table to free

Returns: None
*/
void free_table(Table* table);

/*
Purpose: Returns the value associated with a given ID in a lookup table

Parameters:

Returns:
*/
char* lookup_by_id(Table* table, unsigned int id);

/*
Purpose: Returns the ID associated with a given value in a lookup table

Parameters:

Returns:
*/
unsigned int lookup_by_value(Table* table, char* value);

/*
Purpose: Creates a neighbourhood with a given ID and name

Parameters:

Returns:
*/
Neighbourhood* create_neighbourhood(unsigned int id, char* name);

/*
Purpose: Frees the memory associated with a neighbourhood

Parameters:

Returns:
*/
void free_neighbourhood(Neighbourhood* neighbourhood);

/*
Purpose: Creates an empty neighbourhood table with a given capacity

Parameters:

Returns:
*/
NeighbourhoodTable* create_neighbourhood_table(unsigned int capacity);

/*
Purpose: Frees the memory associated with a neighbourhood table

Parameters:

Returns:
*/
void free_neighbourhood_table(NeighbourhoodTable* table);

/*
Purpose: Adds a neighbourhood to a neighbourhood table

Parameters:

Returns:
*/
void add_neighbourhood(NeighbourhoodTable* table, unsigned int id, char* name);

/*
Purpose: Gets the name of a neighbourhood with a given ID

Parameters:

Returns:
*/
char* get_neighbourhood_by_id(NeighbourhoodTable* table, unsigned int id);

/*
Purpose: Gets the ID of a neighbourhood with a given name

Parameters:

Returns:
*/
unsigned int get_neighbourhood_by_name(NeighbourhoodTable* table, char* name);

#endif