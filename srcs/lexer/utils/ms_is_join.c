#include "minishell.h"
#include "lexer.h"

int	ms_is_join(t_shell *shell)
{
	if (shell->cursor_array->size > 0 && ms_get_parent(shell, 1) != NULL && (ms_get_parent(shell, 1)->type == CMD_JOIN || ms_get_parent(shell, 1)->type == CMD_JOIN_NO_PRINT))
		return (1);
	return (0);
}