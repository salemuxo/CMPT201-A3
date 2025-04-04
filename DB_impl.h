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

Returns: Table* - the pointer to the created table
*/
Table* create_table(unsigned int size);

/*
Purpose: Adds a value to a table

Parameters:
    Table* table: the table to add to
    char* value: the value to add

Returns: None
*/
void add_to_table(Table* table, char* value);

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
    Table* table: the table to lookup in
    unsigned int id: the id to lookup

Returns: char* - the value for the id
*/
char* lookup_by_id(Table* table, unsigned int id);

/*
Purpose: Returns the ID associated with a given value in a lookup table

Parameters:
    Table* table: the table to lookup in
    char* value: the value to lookup

Returns: unsigned int - the id for the value
*/
unsigned int lookup_by_value(Table* table, char* value);

/*
Purpose: Creates a neighbourhood with a given ID and name

Parameters:
    unsigned int id: the neighbourhood id
    char* name: the neighbourhood name

Returns: Neighbourhood* - a pointer to the neighbourhood
*/
Neighbourhood* create_neighbourhood(unsigned int id, char* name);

/*
Purpose: Frees the memory associated with a neighbourhood

Parameters:
    Neighbourhood* neighbourhood: the neighbourhood to free

Returns: None
*/
void free_neighbourhood(Neighbourhood* neighbourhood);

/*
Purpose: Creates an empty neighbourhood table with a given capacity

Parameters:
    unsigned int capacity: the number of neighbourhoods that the table can hold

Returns: NeighbourhoodTable* - a pointer to the table
*/
NeighbourhoodTable* create_neighbourhood_table(unsigned int capacity);

/*
Purpose: Frees the memory associated with a neighbourhood table

Parameters:
    NeighbourhoodTable* table: the table to free

Returns: None
*/
void free_neighbourhood_table(NeighbourhoodTable* table);

/*
Purpose: Adds a neighbourhood to a neighbourhood table

Parameters:
    NeighbourhoodTable* table: the table to add to
    unsigned int id: the id of the neighbourhood
    char* name: the name of the neighbourhood

Returns: None
*/
void add_neighbourhood(NeighbourhoodTable* table, unsigned int id, char* name);

/*
Purpose: Gets the name of a neighbourhood with a given ID

Parameters:
    NeighbourhoodTable* table: the table to search in
    unsigned int id: the id to search for

Returns: char* - the name of the neighbourhood
*/
char* get_neighbourhood_by_id(NeighbourhoodTable* table, unsigned int id);

/*
Purpose: Gets the ID of a neighbourhood with a given name

Parameters:
    NeighbourhoodTable* table: the table to search in
    char* name: the name to search for

Returns: unsigned int - the id of the neighbourhood
*/
unsigned int get_neighbourhood_by_name(NeighbourhoodTable* table, char* name);

/*
Purpose: Returns a Picnic Table based on its ID in the database

Parameters:
    int tableID: the index of the table in the database

Returns: PicnicTable* - a pointer to the picnic table
*/
PicnicTable* get_picnic_table_by_id(int tableID);

void freePicnicTable(PicnicTable* table);

/*
Purpose: Initializes and allocates memory for the database

Parameters: None

Returns: None
*/
void initializeDataBase();

/*
Purpose: The purpose of this function is to look up a value and if it exist t will return its index and if it dosent it will add it adn return its index

Parameters: 
    char* value - the string to look for 
    Table* table - the table we are checking in 

    Return: The index of the value in the table
*/
int lookupOrAdd(char *value, Table *table);

/*
Purpose: The purpose of this function is to check if a negihbourhood with a given id exists in the neighbourhood table 

Parameters: Id , name , ntable 

Return: The id of the neighbourhood
*/
int getOrAddNeighbourhood(int id, char *name, NeighbourhoodTable *ntable);

/*
Purpose: This functions reads data from a csv file and import each line into picnicTableTAble
        it also manages all the lookup tables
        
Paramters: filename - the name of the csv file

Return: None
*/
void importDB(const char *filename);

int compareTableType(const void* a, const void* b);

int compareSurfaceMaterial(const void* a, const void* b);

int compareStructuralMaterial(const void* a, const void* b);

int compareNeighbourhoodID(const void* a, const void* b);

int compareNeighbourhoodName(const void* a, const void* b);

int compareWard(const void* a, const void* b);


#endif