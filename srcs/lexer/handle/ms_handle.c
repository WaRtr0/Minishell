
#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "prompt.h"
#include "utils.h"
#include "env.h"
#include "exec.h"
#include "lexer.h"

int ms_handle(t_array *array, t_shell *shell, int fd[2])
{
	printf("EXEC... [%d]\n", shell->in_pipe);
	int	t_fd[2];
	if (!shell->prompt_listen)
		return (0);
	size_t i;
	t_command *command;
	
	shell->in_pipe = 0;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_JOIN)
			ms_handle_join(command->content.array, shell, fd);
		else if (command->type == CMD_AND_IF && !shell->status)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_OR && shell->status)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_SEMICOLON)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_PIPE)
			ms_handle_pipe(command->content.array, shell, fd);
		else if (command->type == CMD_PARENTHESIS)
		{
			t_fd[0] = fd[0];
			t_fd[1] = fd[1];
			if (i + 1 < array->size)
			{
				command = (t_command *)array->data[i + 1];
				if (command->type == CMD_JOIN_NO_PRINT)
					ms_get_fd(command->content.array, shell, t_fd);
				command = (t_command *)array->data[i];
			}
			ms_handle(command->content.array, shell, t_fd);
		}
		i++;
	}
	return (1);
}