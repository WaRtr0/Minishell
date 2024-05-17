#include "lexer.h"

void ms_append_quote(t_shell *shell)
{
	t_command *append_command;

	if (shell->command != NULL)
	{
		append_command = malloc(sizeof(t_command));
		append_command->type = CMD_TEXT;
		append_command->content.str = shell->command;
		ft_arr_append(shell->cursor, append_command);
		shell->command = NULL;
	}
}