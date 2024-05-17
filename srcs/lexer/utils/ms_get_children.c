#include "lexer.h"

t_command   *ms_get_children(t_shell *shell, size_t children)
{
    size_t size_array;
    size_t size_cursor;

    size_array = shell->cursor_array->size;
    if (size_array == 0 ||  1 > size_array)
        return (NULL);
    size_cursor = ((t_array *)shell->cursor_array->data[size_array - 1])->size;
    if (size_cursor == 0 || children <= 0 || children > size_cursor)
        return (NULL);
    return ((t_command *)(((t_array *)shell->cursor_array->data[size_array - 1])->data[size_cursor - children]));
}