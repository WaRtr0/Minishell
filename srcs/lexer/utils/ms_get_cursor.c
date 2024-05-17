#include "lexer.h"

t_command	*ms_get_cursor(t_shell *shell)
{
	if (((t_array *)shell->cursor)->size > 0)
	{
		return (
			(t_command *)(
				(t_array *)shell->cursor
				)->data[
					(
						(t_array *)shell->cursor
					)->size - 1
				]
		);
	}
	return (NULL);
}