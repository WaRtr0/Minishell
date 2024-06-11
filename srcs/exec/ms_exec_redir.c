/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:37:24 by gcros             #+#    #+#             */
/*   Updated: 2024/06/11 16:19:03 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "put.h"
#include "conf.h"
#include "errno.h" 

int	get_heredoc(t_exec *exec, t_command *cmd);
int	get_redin(t_exec *exec, t_command *cmd);
int	get_redout(t_exec *exec, t_command *cmd);
int	red_error(char *file);

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
			f = get_redout;
		if (f != NULL)
			if (f(exec, (t_command *)exec->redir->data[i]))
				break ;
		i++;
	}
	return (i == exec->redir->size);
}

int	get_heredoc(t_exec *exec, t_command *cmd)
{
	(void) exec;
	(void) cmd;
	if (dup2(cmd->content.fd, exec->dfl_fds[0]) == -1)
	{
		red_error("heredoc");
		return (1);
	}
	return (0);
}

int	get_redin(t_exec *exec, t_command *cmd)
{
	int	fd;

	errno = 0;
	fd = open(cmd->content.str, O_RDONLY);
	if (fd == -1 || dup2(fd, exec->dfl_fds[0]) == -1)
	{
		red_error(cmd->content.str);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	get_redout(t_exec *exec, t_command *cmd)
{
	int					fd;
	const unsigned long	c_flags = (S_IRUSR | S_IWUSR | S_IRGRP
			| S_IWGRP | S_IROTH);
	const unsigned long	o_flags = (O_CREAT | O_WRONLY)
		| (O_TRUNC * cmd->type == CMD_REDIR_OUT)
		| (O_APPEND * cmd->type == CMD_APPEND);

	errno = 0;
	fd = -1;
	if ((get_file_status(cmd->content.str) & fs_is_dir) == 0)
		fd = open(cmd->content.str, o_flags, c_flags);
	else
		errno = EISDIR;
	if (fd == -1 || dup2(fd, exec->dfl_fds[1]) == -1)
	{
		red_error(cmd->content.str);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	red_error(char *file)
{
	char	*err_msg;

	err_msg = ft_strjoin("mishell: redir: ", file);
	if (err_msg == NULL)
		return (1);
	perror(err_msg);
	free(err_msg);
	return (1);
}
