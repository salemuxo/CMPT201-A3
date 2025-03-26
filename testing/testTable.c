#include <stdio.h>
#include "../DB.h"
#include "../DB_impl.h"

int main()
{
    Table* tableTypeTable = create_table(3, "Other Table", "Round Picnic Table", "Square Picnic Table");

    printf("%s\n", tableTypeTable->values[0]);
    printf("%s\n", tableTypeTable->values[1]);
    printf("%s\n", tableTypeTable->values[2]);

    free_table(tableTypeTable);

    
}