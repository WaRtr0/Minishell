#include "lexer.h"

void ms_exit_pipeline(t_shell *shell)
{
	if (ms_is_pipeline(shell))
		shell->cursor = ft_arr_pop(shell->cursor_array);
}