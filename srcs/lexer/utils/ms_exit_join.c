#include "lexer.h"

void ms_exit_join(t_shell *shell)
{
	if (ms_is_join(shell))
		shell->cursor = ft_arr_pop(shell->cursor_array);
}