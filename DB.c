/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Salem, Berhan, Benjamin, Jonathan
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Ardy RD
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int countEntries(char *memberName, char * value)
{
    unsigned int counter = 0;
    // table type
    if (strcmp(memberName, "tableTypeID") == 0)
    {
        // loop through picnic tables
        for (unsigned int i = 0; i < Db->size; i++)
        {
            // if table type of current table matches value, increment counter
            if (Db->picnicTableTable[i]->tableTypeID == atoi(value))
            {
                counter++;
            }
        }
    }
    // surface material
    else if (strcmp(memberName, "surfaceMaterialID") == 0)
    {
        // loop through picnic tables
        for (unsigned int i = 0; i < Db->size; i++)
        {
            // if table type of current table matches value, increment counter
            if (Db->picnicTableTable[i]->surfaceMaterialID == atoi(value))
            {
                counter++;
            }
        }
    }
    // structural material
    else if (strcmp(memberName, "structuralMaterialID") == 0)
    {
        // loop through picnic tables
        for (unsigned int i = 0; i < Db->size; i++)
        {
            // if table type of current table matches value, increment counter
            if (Db->picnicTableTable[i]->structuralMaterialID == atoi(value))
            {
                counter++;
            }
        }
    }
    // neighbourhood ID
    else if (strcmp(memberName, "neighbourhoodID") == 0)
    {
        // loop through picnic tables
        for (unsigned int i = 0; i < Db->size; i++)
        {
            // if table type of current table matches value, increment counter
            if (Db->picnicTableTable[i]->neighbourhoodID == atoi(value))
            {
                counter++;
            }
        }
    }
    // neighbourhood name
    else if (strcmp(memberName, "neighbourhood") == 0)
    {
        // loop through picnic tables
        for (unsigned int i = 0; i < Db->size; i++)
        {
            // if table type of current table matches neighbourhood name corresponding to id, increment counter
            if (Db->picnicTableTable[i]->neighbourhoodID == get_neighbourhood_by_name(Db->neighbourhoodTable, value))
            {
                counter++;
            }
        }
    }
    // ward
    else if (strcmp(memberName, "ward") == 0)
    {
        // loop through picnic tables
        for (unsigned int i = 0; i < Db->size; i++)
        {
            // if table type of current table matches value, increment counter
            if (Db->picnicTableTable[i]->ward == atoi(value))
            {
                counter++;
            }
        }
    }
    // not found
    else
    {
        fprintf(stderr, "Member not found.\n");
    }
    return counter;
}

void editTableEntry(int tableID, char *memberName, char *value)
{
    PicnicTable* table = get_picnic_table_by_id(tableID);
    int id = atoi(value);


    // table type
    if (strcmp(memberName, "tableTypeID") == 0)
    {
        // needs to be added
        if (id >= Db->tableTypeTable->size)
        {
            add_to_table(Db->tableTypeTable, value);
        }
        table->tableTypeID = id;
    }
    // surface material
    else if (strcmp(memberName, "surfaceMaterialID") == 0)
    {
        // needs to be added
        if (id >= Db->surfaceMaterialTable->size)
        {
            add_to_table(Db->surfaceMaterialTable, value);
        }
        table->surfaceMaterialID = id;
    }
    // structural material
    else if (strcmp(memberName, "structuralMaterialID") == 0)
    {
        // needs to be added
        if (id >= Db->structuralMaterialTable->size)
        {
            add_to_table(Db->structuralMaterialTable, value);
        }
        table->structuralMaterialID = id;
    }
    else
    {
        fprintf(stderr, "Member not found.\n");
    }
}

void sortByMember(char *memberName) {
    //Determine sorting criteria and pass comparison function to qsort
    //Support sort by: Table, Surface, Structural, Neighbourhood ID's and ward number
    if (Db == NULL || Db->size == 0) return;

    //Determine function based on memberName
    int(*compare)(const void*, const void*);

    if (strcmp(memberName, "tableTypeID") == 0) {
        compare = compareTableType;
    }
    else if (strcmp(memberName, "surfaceMaterialID") == 0) {
        compare = compareSurfaceMaterial;
    }

    else if (strcmp(memberName, "structuralMaterialID") == 0) {
        compare = compareStructuralMaterial;
    }

    else if (strcmp(memberName, "neighbourhoodID") == 0) {
        compare = compareNeighbourgoodID;
    }

    //we'll need to be able to search a neighbourhood by either ID as above ^^^ or by name into ID as below
    else if (strcmp(memberName, "neighbourhood") == 0) {
        compare = compareNeighbourhoodName;
    }

    else if (strcmp(memberName, "ward") == 0) {
        compare = compareWard;
    }
    else {
        //Member name doesn't match any of the above, either i've missed something or it's invalid
        fprintf(stderr, "Invalid Sorting Member\m");
        return;
    }

    //Use standard library qsort for the picnic table array
    qsort(Db->picnicTableTable, Db->size, sizeof(PicnicTable*), compare);
}

//Comparison Function for table type
int compareTableType(const void* a, const void* b) {
    //Cast from void* to PicnicTable and deference to get actual
    const PicnicTable* tableA = *(const PicnicTable**)a;
    const PicnicTable* tableB = *(const PicnicTable**)b;
    //if result is negative, a comes before b
    //if zero, equal
    //if positive, a comes after b
    return tableA->tableTypeID - tableB->tableTypeID;
}

//Comparison function for suface material
int compareSurfaceMaterial(const void* a, const void* b) {
    //Cast from void* to PicnicTable and deference to get actual
    const PicnicTable* tableA = *(const PicnicTable**)a;
    const PicnicTable* tableB = *(const PicnicTable**)b;
    //if result is negative, a comes before b
    //if zero, equal
    //if positive, a comes after b
    return tableA->surfaceMaterialID - tableB->surfaceMaterialID;
}

//Comparison function for structural material
int compareStructuralMaterial(const void* a, const void* b) {
    //Cast from void* to PicnicTable and deference to get actual
    const PicnicTable* tableA = *(const PicnicTable**)a;
    const PicnicTable* tableB = *(const PicnicTable**)b;
    //if result is negative, a comes before b
    //if zero, equal
    //if positive, a comes after b
    return tableA->structuralMaterialID - tableB->structuralMaterialID;
}

// Comparison function for neighbourhood ID
int compareNeighbourhoodID(const void* a, const void* b) {
    //Cast from void* to PicnicTable and deference to get actual
    const PicnicTable* tableA = *(const PicnicTable**)a;
    const PicnicTable* tableB = *(const PicnicTable**)b;
    //if result is negative, a comes before b
    //if zero, equal
    //if positive, a comes after b
    return tableA->neighbourhoodID - tableB->neighbourhoodID;
}

//compareNeighbourhoodName will need to use get_neighbourhood_by_id to compare properly (Convert Id into name)
int compareNeighbourhoodName(const void* a, const void* b) {
    //Cast from void* to PicnicTable and deference to get actual
    const PicnicTable* tableA = *(const PicnicTable**)a;
    const PicnicTable* tableB = *(const PicnicTable**)b;
    const char* nameA = get_neighbourhood_by_id(Db->neighbourhoodTable, tableA->neighbourhoodID);
    const char* nameB = get_neighbourhood_by_id(Db->neighbourhoodTable, tableB->neighbourhoodID);
    //just use string compare to compare the literal name
    return strcmp(nameA, nameB);
}

// Comparison function for ward
int compareWard(const void* a, const void* b) {
    //Cast from void* to PicnicTable and deference to get actual
    const PicnicTable* tableA = *(const PicnicTable**)a;
    const PicnicTable* tableB = *(const PicnicTable**)b;
    //if result is negative, a comes before b
    //if zero, equal
    //if positive, a comes after b
    return tableA->ward - tableB->ward;
}

//Function to free all dynamic memory
void freeDB() {
    if (Db == NULL) return;

    //Free all PicnicTable Entries
    for (unsigned int i = 0; i < DB->size; i++) {
        if (Db->picknicTableTable [i] != NULL) {
            free(Db->picnicTableTable[i]);
        }
    }
    free(Db->picnicTableTable);

    //Free string tables and contents
    //Outsource to a helper function
    freeStringTable(Db->tableTypeTable);
    freeStringTable(Db->surfaceMaterialTable);
    freeStringTable(Db->structuralMaterialTable);
    freeStringTable(Db->neighbourhoodTable);

    //Free the DB structure itself
    free(Db);
    //prevent weird pointer
    Db = NULL;
}

//String table helper function
static void freeStringTable(StringTable* table) {
    if (table == NULL) return;

    //free each string in table
    for (unsigned int i = 0; i < table->size; i++) {
        free(table->strings[i]);
    }
        //Free the array
        free(table->strings);
        //free the table structure
        free(table);
}
