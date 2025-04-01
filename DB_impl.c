/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Salem, Berhan, Benjamin, Jonathan
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Ardy RD
 */

#include "DB.h"      
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

DataBase *Db = NULL;  // Defining database struct -Berhan
#define DB_ALLOC_SIZE 2000 // i was going to change INIT_SIZE due to it givng me a segmentation dump error but we arent allowed to change it so i created this variable to set my own size

Table* create_table(unsigned int size)
{
    // allocate memory for Table struct
    Table* create = malloc(sizeof(Table));
    if (create == NULL)
    {
        fprintf(stderr, "Memory allocation failed.");
        return NULL;
    }

    // allocate memory for values
    create->values = calloc(size, sizeof(char*));
    if (create->values == NULL)
    {
        fprintf(stderr, "Memory allocation failed.");
        free(create);
        return NULL;
    }

    create->capacity = size;
    create->size = 0;

    return create;
}

void add_to_table(Table* table, char* value)
{
    if (table->size >= table->capacity)
    {
        return;
    }
 
    table->values[table->size] = malloc(strlen(value) + 1);
    if (table->values[table->size] == NULL)
    {
        fprintf(stderr, "Memory allocation failed.");
        return;
    }

    strcpy(table->values[table->size], value);
    table->size++;
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
    if (table->capacity <= id) 
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
        fprintf(stderr, "Memory allocation failed.");
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
        fprintf(stderr, "Memory allocation failed.");
        return NULL;
    }

    create->neighbourhoods = calloc(capacity, sizeof(Neighbourhood*));
    if (create->neighbourhoods == NULL)
    {
        fprintf(stderr, "Memory allocation failed.");
        return NULL;
    }

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

void initializeDataBase(){ //-Berhan   
    Db = malloc(sizeof(DataBase)); // allocates memory for the entire database structure
    
    Db->tableTypeTable = create_table(5);

    Db->surfaceMaterialTable = create_table(5);

    Db->structuralMaterialTable = create_table(5);

    Db->neighborhoodTable = create_neighbourhood_table(500);

    Db->picnicTableTable = malloc(10000 * sizeof(PicnicTable)); // allocated memory to hold picninc table structs
}

int lookupOrAdd(char *value, Table *table) { //-Berhan

    // This loops through the tbale and if the value is the same as the input value it will return the index 
    int id = lookup_by_value(table, value);

    if (id == -1)
    {
        // If the value is not in the table, add it
        add_to_table(table, value);

        return lookup_by_value(table, value);
    }

    return id;
}

int getOrAddNeighbourhood(int id, char *name, NeighbourhoodTable *ntable) { //-Berhan
    /// this loops throguh the id's in the table to the input id and if they match i return it
    if (strcmp(get_neighbourhood_by_id(ntable, id), name) == 0)
    {
        return id;
    }
    
    //if no id then that means i have to add it to the neighbourhood
    add_neighbourhood(ntable, id, name);
    

    return id;
}

void importDB(const char *filename) { //-Berhan

    initializeDataBase(); // this sets up the database and allocates memory for all tables


    FILE *file = fopen(filename, "r");// opens the csv file in read mode
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);//error message if file can't be opened
        return;
    }

    char line[1024]; // buffer to hold each line of the csv
    fgets(line, sizeof(line), file); //skips the first line since it's the csv header

    int picnicIndex = 0;//this keeps track of how many picnic table entries we've added

    while (fgets(line, sizeof(line), file)) {
        
        char *token; // used to hold each field while parsing CSV line by line

        int startingId; //this is the id from the csv file which represents each picnic table
       
        char *tableType; // this holds the table type 
        char *surfaceMaterial; // this holds the surface/table material
        char *structuralMaterial; // this holds the table/structutal material 
        char *street;// this holds the street name
        
        // neighbourhood info from csv
        int neighbourhoodId; 
        char *neighbourhoodName;
       
       // this holds the location information
        int ward;
        double latitude; // latitude of picnic tbale
        double longitude; // longititude of picnic table
        




        // I had to convert the Id's which were strings into ints and the latitude and longitide into floats and these resources helped
        // https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm 
        //https://www.tutorialspoint.com/c_standard_library/c_function_atof.htm
        
        
        // ID
        token = strtok(line, ","); // parse the first field (Id)
        if (!token) continue; // if there's no token, skip this line
        startingId = atoi(token); // convert the ID from string to int

        // Table Type
        tableType = strtok(NULL, ","); // parse the table type (e.g., "Square Picnic Table")
        if (!tableType) continue; // if table type is missing, skip this line

        // Surface Material
        surfaceMaterial = strtok(NULL, ","); // parse the surface material (e.g., "Wood")
        if (!surfaceMaterial) continue; // if surface material is missing, skip this line

        // Structural Material
        structuralMaterial = strtok(NULL, ","); // parse the structural material (e.g., "Metal")
        if (!structuralMaterial) continue; // if structural material is missing, skip this line

        // Street / Avenue
        street = strtok(NULL, ","); // parse the street/avenue name
        if (!street) continue; // if street is missing, skip this line

        // Neighbourhood ID
        token = strtok(NULL, ","); // parse the neighbourhood ID
        if (!token) continue; // if neighbourhood ID is missing, skip this line
        neighbourhoodId = atoi(token); // convert neighbourhood ID from string to int

        // Neighbourhood Name
        neighbourhoodName = strtok(NULL, ","); // parse the neighbourhood name
        if (!neighbourhoodName) continue; // if neighbourhood name is missing, skip this line

        // Ward
        token = strtok(NULL, ","); // parse the ward (e.g., "WARD 05")
        if (!token) continue; // if ward is missing, skip this line
        sscanf(token, "WARD %d", &ward); // extract the ward number from the string (e.g., "WARD 05" → 5)

        // Latitude
        token = strtok(NULL, ","); // parse the latitude value
        if (!token) continue; // if latitude is missing, skip this line
        latitude = atof(token); // convert latitude from string to double

        // Longitude
        token = strtok(NULL, ","); // parse the longitude value
        if (!token) continue; // if longitude is missing, skip this line
        longitude = atof(token); // convert longitude from string to double



        int tableTypeId = lookupOrAdd(tableType, Db->tableTypeTable); // checks if table type exists, adds if not, then returns the id
        int surfaceId = lookupOrAdd(surfaceMaterial, Db->surfaceMaterialTable); // same idea for surface material
        int structuralId = lookupOrAdd(structuralMaterial, Db->structuralMaterialTable); // same for structural material
        getOrAddNeighbourhood(neighbourhoodId, neighbourhoodName, Db->neighborhoodTable); // makes sure the neighbourhood is in the table (adds it if not)


        PicnicTable *pt = malloc(sizeof(PicnicTable));// holds all info for one picnic table entry

        pt->sideID = startingId; // this is the original id from the csv
        pt->tableTypeID = tableTypeId; // internal id for table type
        pt->surfaceMaterialID = surfaceId; // internal id for surface material
        pt->structuralMaterialID = structuralId; // internal id for structural material

        pt->streetAvenue = malloc(strlen(street) + 1); 
        if (pt->streetAvenue == NULL)
        {
            fprintf(stderr, "Memory allocation failed.");
            return;
        }
        strcpy(pt->streetAvenue, street);

        pt->neighbourhoodID = neighbourhoodId; // saves the real neighbourhood id from the csv
        pt->ward = ward; // ward number from csv
        pt->latitude = latitude; // latitude coordinate from csv
        pt->longitude = longitude; // longitiude coordinate from csv

        Db->picnicTableTable[picnicIndex++] = pt; // store the entry in the array and move to the next index

    }

    fclose(file);
    printf("Successfully imported %d picnic tables from %s\n", picnicIndex, filename); // i added this to make sure it was importing everything( i will only loop through the first 10 )
}

