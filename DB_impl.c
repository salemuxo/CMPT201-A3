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
void initializeDataBase(){ //-Berhan
    /*
       Purpose: The purpose of this function is initalize and allocate memory for all the database tables
       Parameters: None
       Return: None

    */
   
          Db = malloc(sizeof(DataBase)); // allocates memory for the entire database structure
          
          Db->tableTypeTable = malloc(sizeof(Table)); // allocates memory for the tableType table
          Db->tableTypeTable->values = malloc(DB_ALLOC_SIZE * sizeof(char *)); // allocated string pointers to store tabletype values
          Db->tableTypeTable->size = 0; // i set the starting string to 0 and it will be incrmented on new entrries

          Db->surfaceMaterialTable = malloc(sizeof(Table)); // allocates memory for the surfacematerial Table
          Db->surfaceMaterialTable->values = malloc(DB_ALLOC_SIZE * sizeof(char *)); // allocated string pointers to store surface material values
          Db->surfaceMaterialTable->size = 0;

          Db->structuralMaterialTable = malloc(sizeof(Table)); // allocates memory for the structuralMaterialTable
          Db->structuralMaterialTable->values = malloc(DB_ALLOC_SIZE * sizeof(char *)); // allocated string pointers to store structarle material values
          Db->structuralMaterialTable->size = 0;

          Db->neighborhoodTable = malloc(sizeof(NeighbourhoodTable));// allocates memory for the neighbourhoodTable
          Db->neighborhoodTable->neighbourhoods = malloc(DB_ALLOC_SIZE * sizeof(Neighbourhood)); //allocated string pointers to store neighbourhood structs
          Db->neighborhoodTable->size = 0;

          Db->picnicTableTable = malloc(10000 * sizeof(PicnicTable)); // allocated memory to hold picninc table structs
}

int lookupOrAdd(char *value, Table *table) { //-Berhan
    /*
    Purpose: The purpose of this function is to look up a value and if it exist t will return its index and if it dosent it will add it adn return its index
    Parameters: Value - the string to look for ,Table - the table we are checking in 
    Return:  The index of the value in the table
    */
    
    

    // This loops through the tbale and if the value is the same as the input value it will return the index 
    for(int i = 0;i < table->size;i++ ){

        if(strcmp(table->values[i],value) ==0) {

               return i;
        }
    }
    
    // If the value is not the same the same..
    table->values[table->size] = malloc(strlen(value) + 1); // i allocate memory for the value ( i did +1 for the null terminator)
    strcpy(table->values[table->size], value);// copy the string into the newly allocated memory 
    return table->size++; // return  the current index and increase the size of the table 


}

int getOrAddNeighbourhood(int id, char *name, NeighbourhoodTable *ntable) { //-Berhan
    /*
    
    Purpose: The purpose of this function is to check if a negihbourhood with a given id exists in the neighbourhood table 
    Parameters: Id , name , 
    Return: The id of the neighbourhood
    
    
    */
    
    
    /// this loops throguh the id's in the table to the input id and if they match i return it
    for (int i = 0; i < ntable->size; i++) {
        if (ntable->neighbourhoods[i].id == id) {
            return id;
        }
    }
    
    //if the loop did not return an id then that means i have to add it to the neighbourhood
    ntable->neighbourhoods[ntable->size].id = id; // adding the new id to the next slot in the table
    ntable->neighbourhoods[ntable->size].name = malloc(strlen(name) + 1);//allocate memory fo rthe new neighbourhood name string
    strcpy(ntable->neighbourhoods[ntable->size].name, name);// copy the new neighbourhood string to the new space
    ntable->size++; // increase the size of neighbourhood by one

    return id;
}

void importDB(const char *filename) { //-Berhan

      /*
      Purpose: This functions reads data from a csv file and import each line into picnicTableTAble
               it also manages all the lookup tables
               
      Paramters: filename - the name of the csv file
      Return: None
      
      */

    initializeDataBase(); // this sets up the database and allocates memory for all tables


    FILE *file = fopen(filename, "r");// opens the csv file in read mode
    if (!file) {
        printf("Error: Could not open file %s\n", filename);//error message if file can't be opened
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


PicnicTable pt; // holds all info for one picnic table entry

pt.sideID = startingId; // this is the original id from the csv
pt.tableTypeID = tableTypeId; // internal id for table type
pt.surfaceMaterialID = surfaceId; // internal id for surface material
pt.structuralMaterialID = structuralId; // internal id for structural material
pt.streetAvenue = strdup(street); // makes a copy of the street name string
pt.neighbourhoodID = neighbourhoodId; // saves the real neighbourhood id from the csv
pt.ward = ward; // ward number from csv
pt.latitude = latitude; // latitude coordinate from csv
pt.longitude = longitude; // longitiude coordinate from csv

Db->picnicTableTable[picnicIndex++] = pt; // store the entry in the array and move to the next index

    }

    fclose(file);
    printf("Successfully imported %d picnic tables from %s\n", picnicIndex, filename); // i added this to make sure it was importing everything( i will only loop through the first 10 )
}

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



