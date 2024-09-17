#include <stdio.h>
#include <stdlib.h>

#include "integer.h"

#include "list.c"

u0 print_list(List* list)
{
    printf("List info:\n");
    printf("List data: %u\n", list->data);
    printf("List length: %u\n", list->length);
    printf("List capacity: %u\n", list->capacity);
}

u0 print_elements(List* list)
{
    u0* element = NULL;

    for (u16 index = 0; index < list->length; ++index)
    {
        if (List_get(list, index, &element) == FAIL)
        {
            printf("Couldn't fetch element @ %u.\n", index);
            goto end;
        }

        printf("%u ", element);
    }

end:
    printf("\n");
}

i16 main(void)
{
    printf("Initializing list.\n");

    List list = {};

    if (List_init(&list) == FAIL)
    {
        printf("Couldn't initialize list!\n");
        return 1;
    }

    print_list(&list);

    printf("Filling list with 10 items.\n");

    u16 index;

    for (index = 1; index <= 10; ++index)
    {
        printf("Pushing element '%u' into list.\n", index);

        // All list methods can be checked for success/failure.
        if (List_insert(&list, list.length, (u0*)index) == FAIL)
        {
            printf("Couldn't push element into list!\n");
            goto dispose;
        }
    }

    print_elements(&list);

    printf("Inserting element in the middle.\n");
    List_insert(&list, list.length / 2 - 1, (u0*) 50);
    print_elements(&list);

    printf("Inserting element in the beginning.\n");
    List_insert(&list, 0, (u0*) 60);
    print_elements(&list);

    u0* element = NULL;

    printf("Removing (And popping) the last three elements.\n");
    List_remove(&list, list.length - 1, &element);
    printf("Popped: %u.\n", element);
    List_remove(&list, list.length - 1, &element);
    printf("Popped: %u.\n", element);
    List_remove(&list, list.length - 1, &element);
    printf("Popped: %u.\n", element);
    print_elements(&list);

    printf("Removing (And popping) the first three elements.\n");
    List_remove(&list, 0, &element);
    printf("Popped: %u.\n", element);
    List_remove(&list, 0, &element);
    printf("Popped: %u.\n", element);
    List_remove(&list, 0, &element);
    printf("Popped: %u.\n", element);
    print_elements(&list);

    printf("Setting all elements to 420.\n");
    for (index = 0; index < list.length; ++index)
        List_set(&list, index, (u0*) 420);
    print_elements(&list);

dispose:
    printf("Disposing.\n");

    List_dispose(&list);

    return 0;
}
