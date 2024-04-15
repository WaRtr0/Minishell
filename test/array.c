#include <stdio.h>
#include "arr.h"

int main()
{
    t_array *array;
    int i;

    array = ft_arr_new(2);
    i = 0;
    while (i < 10)
    {
        ft_arr_append(array, (void *)(intptr_t)i);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        printf("%d\n", (int)(intptr_t)array->data[i]);
        i++;
    }
    printf("Array SIZE: %d\n", (int)array->size);
    return (0);
}
