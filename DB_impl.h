/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Ardy RD
 */


#include "DB.h"
#ifndef DB_IMPL_H
#define DB_IMPL_H

Table* create_table(char** values, int size);

void free_table(Table* table);

Neighbourhood* create_neighbourhood(int id, char* name);

void free_neighbourhood(Neighbourhood* neighbourhood);

NeighbourhoodTable* create_neighbourhood_table(Neighbourhood* neighbourhoods, int size);

void free_neighbourhood_table(NeighbourhoodTable* table);

#endif