#include <stdio.h>
#include <stdlib.h>
#include "arr.h"

int main()
{
    t_array *array;
    int i;

    array = ft_arr_new(2);
    i = 0;
    while (i < 10)
    {
        ft_arr_append(array, (void *)i);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        printf("%d\n", (int)array->data[i]);
        i++;
    }
    printf("Array SIZE: %d\n", array->size);
    return (0);
}