/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/04 15:22:42 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "lexer.h"
#include <sys/stat.h>
#include "env.h"
#include "exec.h"
#include "utils.h"
#include "handle.h"

static int	add_word(t_command *command, char **word, t_shell *shell)
{
	char	*tmp;

	if (*word == NULL)
		*word = ft_strdup(command->content.str);
	else
	{
		tmp = *word;
		*word = ft_strjoin(*word, command->content.str);
		free(tmp);
	}
	if (*word == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
		return (1);
	}
	return (0);
}

static int	commit_word(t_exec *exec_cmd, char **word)
{
	if (*word != NULL)
	{
		ft_arr_append(exec_cmd->content, *word);
		*word = NULL;
	}
	return (0);
}

// static int ms_wildcard(t_array *array, size_t *i, t_exec *exec_cmd, char **word)
// {
// 	t_command	*command;
// 	char		*str;
// 	char		*path;
// 	char		*tmp;
// 	command = (t_command *)array->data[*i];
	
// 	if (word != NULL)
// 	{
// 		str = ft_strjoin(*word, "*");
// 		free(*word);
// 		*word = NULL;
// 	}
// 	else
// 		str = ft_strdup("*");
// 	if (str == NULL)
// 		return (1);
	
// 	while ((*i + 1) < array->size )
// 	{
// 		if (((t_command *)array->data[*i + 1])->type == CMD_WILDCARD)
// 		{
// 			tmp = ft_strjoin(str, "*");
// 			free(str);
// 			str = tmp;
// 			*i += 1;
// 		}
// 		else if (((t_command *)array->data[*i + 1])->type == CMD_TEXT)
// 		{
// 			tmp = ft_strjoin(str, ((t_command *)array->data[*i + 1])->content.str);
// 			free(str);
// 			str = tmp;
// 			*i += 1;
// 		}
// 		else
// 			break;
// 	} 
	



// 	if (path == NULL)
// 	{
// 		*i += 1;
// 		return (0);
// 	}


// 	path = ms_pathexp(command->content.str);
// 	ft_arr_append(exec_cmd->content, path);
// 	free(path);
// 	*i += 1;
// 	return (0);
// }

static int	add_exec(t_exec **exec_cmd, t_shell *shell);

static int	run_wildcard(t_wildcard_run *run)
{
	t_command	*command;
	char		*tmp;

	while (run->index < run->array->size && run->shell->error < 1)
	{
		command = (t_command *)run->array->data[run->index];
		if (run->exec_cmd->content->size > 0)
			return (1);
		if (command->type == CMD_TEXT)
			add_word(command, &run->word, run->shell);
		else if (command->type == CMD_EXPAND
			|| command->type == CMD_EXPAND_QUOTE)
			ms_expand(command, run->shell, run->exec_cmd, &run->word);
		else if (command->type == CMD_WILDCARD)
		{
			tmp = run->word;
			run->word = ft_strjoin(run->word, "*");
			if (run->word == NULL)
			{
				run->shell->error = 1;
				run->shell->prompt_listen = 0;
				free(tmp);
				return (0);
			}
			free(tmp);
		}
		else
			return (1);
		run->index++;
	}
	return (0);
}

static t_wildcard_run	*ms_handle_wildcard(t_shell *shell, t_array *array,
	size_t *i, char **word)
{
	t_wildcard_run	*run;

	if (!shell->prompt_listen)
		return (NULL);
	run = malloc(sizeof(t_wildcard_run));
	if (run == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
		return (NULL);
	}
	if (add_exec(&run->exec_cmd, shell) == 0 || run->exec_cmd == NULL)
	{
		free(run);
		return (NULL);
	}
	run->index = *i;
	run->array = array;
	run->shell = shell;
	run->word = *word;
	// printf("IN2 wildcard\n");
	run_wildcard(run);
	return (run);
}

#include "wildcard.h"

static int ms_wildcard(t_array *array, size_t *i, t_exec *exec_cmd, char **word, t_shell *shell)
{
	t_wildcard_run	*run;
	(void) exec_cmd;
	
	//printf("IN wildcard\n");
	if (*word == NULL)
	{
		*word = ft_strdup("");
		if (*word == NULL)
			return (1);
	}
	run = ms_handle_wildcard(shell, array, i, word);
	//printf("OUT wildcard\n");
	if (run == NULL)
		return (0);

	//printf("COUCOU1\n");
	
	if (run->exec_cmd->content->size > 0)
	{
		//printf("COUCOUA\n [%s]\n", (char *)run->exec_cmd->content->data[0]);
		char *tmp;
		tmp = ms_pathexp(run->exec_cmd->content->data[0]);
		if (tmp != NULL)
			ft_arr_append(exec_cmd->content, tmp);
		free(ft_arr_shift(run->exec_cmd->content));
		size_t i = 0;
		while (i < run->exec_cmd->content->size)
		{
			ft_arr_append(exec_cmd->content, run->exec_cmd->content->data[i]);
			i++;
		}
		*word = run->word;
	}
	else
	{
		//printf("COUCOUB\n [%s]\n", run->word);
		*word = ms_pathexp(run->word);
	}
	*i = run->index;
	// word = NULL;
	// free(run->exec_cmd);
	// free(run);

	return (0);
}



static int	run_join(t_array *array, t_exec *exec_cmd,
	t_shell *shell, char **word)
{
	size_t		i;
	t_command	*command;

	i = 0;
	while (i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT)
			add_word(command, word, shell);
		else if (command->type == CMD_EXPAND
			|| command->type == CMD_EXPAND_QUOTE)
			ms_expand(command, shell, exec_cmd, word);
		else if (command->type == CMD_WILDCARD)
			ms_wildcard(array, &i, exec_cmd, word, shell);
		else if (command->type == CMD_EMPTY)
			commit_word(exec_cmd, word);
		else if (command->type == CMD_HEREDOC)
			ms_heredoc_part(array, &i, exec_cmd->fd);
		else if (command->type == CMD_REDIR_IN)
			ms_redir_in_part(array, &i, exec_cmd->fd);
		else if (command->type == CMD_REDIR_OUT)
			ms_redir_out_part(array, &i, exec_cmd->fd);
		else if (command->type == CMD_APPEND)
			ms_append_part(array, &i, exec_cmd->fd);
		i++;
	}
	return (0);
}

static int	add_exec(t_exec **exec_cmd, t_shell *shell)
{
	*exec_cmd = malloc(sizeof(t_exec));
	if (exec_cmd == NULL)
	{
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->content = ft_arr_new(20);
	if ((*exec_cmd)->content == NULL)
	{
		free(*exec_cmd);
		exec_cmd = NULL;
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->fd[0] = -1;
	(*exec_cmd)->fd[1] = -1;
	return (1);
}

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec		*exec_cmd;
	char		*word;

	if (!shell->prompt_listen || g_signal_value != 0)
	{
		if (g_signal_value != 0)
			g_signal_value = 0;
		return (0);
	}
	word = NULL;
	if (add_exec(&exec_cmd, shell) == 0 || exec_cmd == NULL)
		return (0);
	run_join(array, exec_cmd, shell, &word);
	if (exec_cmd->fd[0] == -1)
		exec_cmd->fd[0] = fd[0];
	if (exec_cmd->fd[1] == -1)
		exec_cmd->fd[1] = fd[1];
	if (word != NULL)
		ft_arr_append(exec_cmd->content, word);
	if (exec_cmd->content->size > 0)
		ms_set_status(ms_exec(exec_cmd, shell));
	ms_close_fd(fd, exec_cmd->fd);
	free_exec(exec_cmd);
	return (1);
}
