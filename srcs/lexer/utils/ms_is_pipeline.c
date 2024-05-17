#include "minishell.h"
#include "lexer.h"

int	ms_is_pipeline(t_shell *shell)
{
	if (shell->cursor_array->size > 0 && ms_get_parent(shell, 1) != NULL && ms_get_parent(shell, 1)->type == CMD_PIPE)
		return (1);
	return (0);
}