#include <stdio.h>
#include "../DB.h"
#include "../DB_impl.h"

int main() {
    // import the picnic table data from the csv file
    importDB("dataset/PicnicTable.csv");

    // print the first 10 picnic table entries to check if everything looks good
    for (int i = 0; i < 10; i++) {
        PicnicTable *pt = Db->picnicTableTable[i];

        printf("Site ID: %d | Street: %s | Ward: %d | Lat: %.4f | Lon: %.4f\n",
            pt->siteID, pt->streetAvenue, pt->ward, pt->latitude, pt->longitude);
    }

    // print size of each lookup table to make sure they were filled
    printf("\nTable Type Count: %d\n", Db->tableTypeTable->size);
    printf("Surface Material Count: %d\n", Db->surfaceMaterialTable->size);
    printf("Structural Material Count: %d\n", Db->structuralMaterialTable->size);
    printf("Neighbourhood Count: %d\n", Db->neighbourhoodTable->size);

    return 0;
}
