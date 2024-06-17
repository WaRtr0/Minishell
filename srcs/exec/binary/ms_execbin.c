/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execbin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:52:43 by gcros             #+#    #+#             */
/*   Updated: 2024/06/17 18:11:14 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "str.h"
#include "put.h"
#include "conf.h"

int		on_error(char **envp, char **arg, char *cmd);
char	**get_env(t_env	*env);
char	**get_args(t_array *arr);
int		run_bin(char *cmd, char **args, char **envp);

int	execbin(t_exec *exec, t_shell *shell)
{
	char	**args;
	char	**envp;
	char	*cmd;
	size_t	i;

	ms_sig_set(sig_restore);
	cmd = NULL;
	args = NULL;
	envp = NULL;
	if (get_redir(exec))
		return (free_shell(shell), free_exec(exec), close_all(), 1);
	set_io(exec->dfl_fds);
	close_fds(exec->dfl_fds);
	i = 3;
	while (i < 1024)
		close(i++);
	args = get_args(exec->content);
	envp = get_env(shell->env);
	if (args != NULL)
		cmd = get_bin(args[0], shell->env);
	free_shell(shell);
	free_exec(exec);
	if ((!(size_t)args | !(size_t)envp | !(size_t)cmd))
		return (on_error(envp, args, cmd));
	return (run_bin(cmd, args, envp));
}

int	run_bin(char *cmd, char **args, char **envp)
{
	if (DEBUG_MODE)
		ft_putendl_fd("==run_bin", 2);
	execve(cmd, args, envp);
	ms_set_status(EXIT_FAILURE << 8);
	perror("minishell: execve");
	return (on_error(envp, args, cmd));
}

char	**get_env(t_env *env)
{
	char	**envp;

	if (ms_env_to_strs(env, &envp) == 1)
		return (NULL);
	return (envp);
}

char	**get_args(t_array *arr)
{
	t_array	*new;
	char	**args;

	new = ft_arr_map(arr, (void *(*)(void *))ft_strdup, free);
	if (new == NULL)
		return (NULL);
	if (ft_arr_append(new, NULL) == 0)
		return (ft_arr_free(&arr, free), NULL);
	args = (char **)new->data;
	free(new);
	return (args);
}

int	on_error(char **envp, char **args, char *cmd)
{
	if (args != NULL)
		ft_strsfree(args);
	if (envp != NULL)
		ft_strsfree(envp);
	free(cmd);
	return (ms_get_status());
}
