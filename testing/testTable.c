#include <stdio.h>
#include "../DB.h"
#include "../DB_impl.h"

int main()
{
    Table* tableTypeTable = create_table(3);

    add_to_table(tableTypeTable, "Other Table");
    add_to_table(tableTypeTable, "Round Picnic Table");
    add_to_table(tableTypeTable, "Square Picnic Table");

    printf("ID: %d, Value: %s\n", lookup_by_value(tableTypeTable, "Other Table"), lookup_by_id(tableTypeTable, 0));
    printf("ID: %d, Value: %s\n", lookup_by_value(tableTypeTable, "Round Picnic Table"), lookup_by_id(tableTypeTable, 1));
    printf("ID: %d, Value: %s\n", lookup_by_value(tableTypeTable, "Square Picnic Table"), lookup_by_id(tableTypeTable, 2));

    free_table(tableTypeTable);    
}