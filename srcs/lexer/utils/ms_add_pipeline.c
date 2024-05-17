#include "lexer.h"

void ms_add_pipeline(t_shell *shell)
{
	t_command *append_command;

	if (!ms_is_pipeline(shell))
	{
		append_command = malloc(sizeof(t_command));
		append_command->type = CMD_PIPE;
		append_command->content.array = ft_arr_new(10);
		ft_arr_append(shell->cursor, append_command);
		ft_arr_append(shell->cursor_array, shell->cursor);
		shell->cursor = append_command->content.array;
	}
}