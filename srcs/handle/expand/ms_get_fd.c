#include "minishell.h"
#include "lexer.h"
#include <sys/stat.h>

void	ms_get_fd(t_array *array, t_shell *shell,int *fd)
{
	t_command	*command;
	char		*word;
	(void)shell;
	(void)word;
	int			t_fd[2];
	size_t	i;

	t_fd[0] = -1;
	t_fd[1] = -1;

	word = NULL;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_HEREDOC)
		{
			if (t_fd[0] != -1)
				close(t_fd[0]);
			t_fd[0] = command->content.fd;
		}
		else if (command->type == CMD_REDIR_IN)
		{
			if (t_fd[0] != -1)
				close(t_fd[0]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			t_fd[0] = open(command->content.str, O_RDONLY);
		}
		else if (command->type == CMD_REDIR_OUT)
		{
			if (t_fd[1] != -1)
				close(t_fd[1]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			t_fd[1] = open(command->content.str, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		}
		else if (command->type == CMD_APPEND)
		{
			if (t_fd[1] != -1)
				close(t_fd[1]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			t_fd[1] = open(command->content.str, O_CREAT | O_APPEND | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		}
		i++;
	}

	if (t_fd[0] != -1)
		fd[0] = t_fd[0];
	if (t_fd[1] != -1)
		fd[1] = t_fd[1];
}