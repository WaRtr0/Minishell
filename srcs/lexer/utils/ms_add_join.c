#include "lexer.h"

void ms_add_join(t_shell *shell, int type )
{
	t_command *append_command;

	if (!ms_is_join(shell))
	{
		append_command = malloc(sizeof(t_command));
		append_command->type = CMD_JOIN;
		if (type >= 0)
			append_command->type = type;
		append_command->content.array = ft_arr_new(10);
		ft_arr_append(shell->cursor, append_command);
		ft_arr_append(shell->cursor_array, shell->cursor);
		shell->cursor = append_command->content.array;
	}
}