/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:37:24 by gcros             #+#    #+#             */
/*   Updated: 2024/06/07 16:36:40 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "put.h"
#include "conf.h"

int	get_heredoc(t_exec *exec, t_command *cmd);
int	get_redin(t_exec *exec, t_command *cmd);
int	get_redout(t_exec *exec, t_command *cmd);
int	get_redapp(t_exec *exec, t_command *cmd);

int	get_redir(t_exec *exec)
{
	size_t	i;
	int		(*f)(t_exec *, t_command *);

	f = NULL;
	i = 0;
	save_io(exec->fd, exec->dfl_fds);
	while (i < exec->redir->size)
	{
		f = NULL;
		if (((t_command *)exec->redir->data[i])->type == CMD_HEREDOC)
			f = get_heredoc;
		else if (((t_command *)exec->redir->data[i])->type == CMD_REDIR_IN)
			f = get_redin;
		else if (((t_command *)exec->redir->data[i])->type == CMD_REDIR_OUT)
			f = get_redout;
		else if (((t_command *)exec->redir->data[i])->type == CMD_APPEND)
			f = get_redapp;
		if (f != NULL)
			if (f(exec, (t_command *)exec->redir->data[i]))
				break ;
		i++;
	}
	return (0);
}

int	get_heredoc(t_exec *exec ,t_command *cmd)
{
	(void) exec;
	(void) cmd;
	ft_putendl_fd("get_heredoc", 2);
	//if (dup2(cmd->content.fd, exec->dfl_fds[0]) == -1)
	//{
	//	ft_putendl_fd("error du2", 2);
	//	return (1);
	//}
	return (0);
}

int	get_redin(t_exec *exec ,t_command *cmd)
{
	(void) exec;
	(void) cmd;
	ft_putendl_fd("get_redin", 2);
	return (0);
}

int	get_redout(t_exec *exec ,t_command *cmd)
{
	(void) exec;
	(void) cmd;
	ft_putendl_fd("get_redout", 2);
	return (0);
}

int	get_redapp(t_exec *exec ,t_command *cmd)
{
	(void) exec;
	(void) cmd;
	ft_putendl_fd("get_redapp", 2);
	return (0);
}