#include "../DB.h"
#include "../DB_impl.h"
#include <stdio.h>

int main()
{
    importDB("dataset/PicnicTable.csv");

    printf("\nTABLE TYPE\n");
    printf("Before: %d\n", get_picnic_table_by_id(500)->tableTypeID);
    editTableEntry(500, "tableTypeID", "0");
    printf("After: %d\n", get_picnic_table_by_id(500)->tableTypeID);

    printf("\nSURFACE MATERIAL\n");
    printf("Before: %d\n", get_picnic_table_by_id(500)->tableTypeID);
    editTableEntry(500, "surfaceMaterialID", "1");
    printf("After: %d\n", get_picnic_table_by_id(500)->surfaceMaterialID);

    printf("\nSTRUCTURAL MATERIAL\n");
    printf("Before: %d\n", get_picnic_table_by_id(500)->structuralMaterialID);
    editTableEntry(500, "structuralMaterialID", "2");
    printf("After: %d\n", get_picnic_table_by_id(500)->structuralMaterialID);
}