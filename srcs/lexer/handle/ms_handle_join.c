
#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "prompt.h"
#include "utils.h"
#include "env.h"
#include "exec.h"

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec	    *exec_cmd;
	t_command	*command;
	char		*word;
	size_t	i;
	if (!shell->prompt_listen)
		return (0);

	exec_cmd = malloc(sizeof(t_exec));
	exec_cmd->content = ft_arr_new(20);
	exec_cmd->fd[0] = -1;
	exec_cmd->fd[1] = -1;

	word = NULL;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT)
		{
			if (!word)
				word = ft_strdup("");
			word = ft_strjoin(word, command->content.str);
		}
		else if (command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
		{
			if (word == NULL)
				word = ft_strdup("");

			//special
			if (!ft_strlen(command->content.str))
				word = ft_strjoin(word, "$");
			else
			{
				shell->command =  ms_env_get(shell->env,command->content.str);
				if (command->type != CMD_EXPAND_QUOTE)
				{
					if (shell->command != NULL && shell->command[0])
					{
						char	**temp_char;
						int		temp;
						
						temp = ft_include(" \t", shell->command[0]);
						
						temp_char = ft_split_chars(shell->command, " \t");
						if (*temp_char != NULL && !temp)
						{
							word = ft_strjoin(word, temp_char[0]);
							if ((*(temp_char + 1)) != NULL)
							{
								ft_arr_append(exec_cmd->content, word);
								word = NULL;
							}
							temp_char++;
						}
						while (*temp_char != NULL)
						{
							if ((*(temp_char + 1)) != NULL)
								ft_arr_append(exec_cmd->content, temp_char);
							else
								word = *temp_char;
							temp_char++;
						}
					}
				}
				else if (shell->command != NULL)
					word = ft_strjoin(word, ft_strdup(shell->command));	
				shell->command = NULL;
			}
			
		}
		else if (command->type == CMD_EMPTY)
		{
			if (word != NULL)
				ft_arr_append(exec_cmd->content, word);
			word = NULL;
		}
		else if (command->type == CMD_HEREDOC)
		{
			if (exec_cmd->fd[0] != -1)
				close(exec_cmd->fd[0]);
			exec_cmd->fd[0] = command->content.fd;
		}
		else if (command->type == CMD_REDIR_IN)
		{
			if (exec_cmd->fd[0] != -1)
				close(exec_cmd->fd[0]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			exec_cmd->fd[0] = open(command->content.str, O_RDONLY);
		}
		else if (command->type == CMD_REDIR_OUT)
		{
			if (exec_cmd->fd[1] != -1)
				close(exec_cmd->fd[1]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			exec_cmd->fd[1] = open(command->content.str, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		}
		else if (command->type == CMD_APPEND)
		{
			if (exec_cmd->fd[1] != -1)
				close(exec_cmd->fd[1]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			exec_cmd->fd[1] = open(command->content.str, O_CREAT | O_APPEND | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		}
		i++;
	}

	if (exec_cmd->fd[0] == -1)
		exec_cmd->fd[0] = fd[0];
	if (exec_cmd->fd[1] == -1)
		exec_cmd->fd[1] = fd[1];
		
	if (word != NULL)
		ft_arr_append(exec_cmd->content, word);
	
	// GCROS
	if (exec_cmd->content->size > 0)
		ms_exec(exec_cmd, shell);
	// END-GCROS
	if (DEBUG_MODE)
	{
		printf("JOIN... [%d]\n", shell->in_pipe);
		printf(C_YELLOW"FD: %d | %d"C_RESET, exec_cmd->fd[0], exec_cmd->fd[1]);
		while (exec_cmd->content->size > 0)
		{
			word = exec_cmd->content->data[0];
			printf("\n%s", word);
			ft_arr_shift(exec_cmd->content);
		}
	}
	
	if (DEBUG_MODE && exec_cmd->fd[0] != 0)
	{
		printf(C_BLUE"\nOUTPUT [%d | %d]:\n"C_RESET, exec_cmd->fd[0], exec_cmd->fd[1]);
		char *buffer = ft_calloc(sizeof(char), 100);;
		ft_strcpy(buffer, "empty");
		read((int)exec_cmd->fd[0], buffer, 100);
		printf(C_BLUE"%s\n"C_RESET, buffer);
		free(buffer);
	}
	printf("\n");
	return (1);
}