#include "../DB.h"
#include "../DB_impl.h"
#include <stdio.h>

int main()
{
    importDB("dataset/PicnicTable.csv");

    printf("\nTABLE TYPE\n");
    printf("0: %d\n", countEntries("tableTypeID", "0"));
    printf("1: %d\n", countEntries("tableTypeID", "1"));
    printf("2: %d\n", countEntries("tableTypeID", "2"));

    printf("\nSURFACE MATERIAL\n");
    printf("0: %d\n", countEntries("surfaceMaterialID", "0"));
    printf("1: %d\n", countEntries("surfaceMaterialID", "1"));
    printf("2: %d\n", countEntries("surfaceMaterialID", "2"));

    printf("\nSTRUCTURAL MATERIAL\n");
    printf("0: %d\n", countEntries("structuralMaterialID", "0"));
    printf("1: %d\n", countEntries("structuralMaterialID", "1"));
    printf("2: %d\n", countEntries("structuralMaterialID", "2"));

    printf("\nNEIGHBOURHOOD ID\n");
    printf("6620: %d\n", countEntries("neighbourhoodID", "6620"));
    printf("5220: %d\n", countEntries("neighbourhoodID", "5220"));

    printf("\nNEIGHBOURHOOD NAME\n");
    printf("RIVER VALLEY GOLD BAR: %d\n", countEntries("neighbourhood", "RIVER VALLEY GOLD BAR"));
    printf("GREENFIELD: %d\n", countEntries("neighbourhood", "GREENFIELD"));

    printf("\nWARD\n");
    printf("08: %d\n", countEntries("ward", "08"));
    printf("10: %d\n", countEntries("ward", "10"));

}