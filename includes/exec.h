/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:50:41 by gcros             #+#    #+#             */
/*   Updated: 2024/06/21 14:58:04 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

enum e_file_status
{
	fs_default = 0,
	fs_exist = 1 << 0,
	fs_exec = 1 << 1,
	fs_read = 1 << 2,
	fs_write = 1 << 3,
	fs_is_dir = 1 << 4,
};

int					ms_exec(t_exec *exec, t_shell *shell);

int					ms_run_builtin(t_exec *exec, t_shell *shell);
int					ms_exec_builtin(t_exec *exec, t_shell *shell);
int					fork_no_exec(t_exec *exec, t_shell *shell);

int					restore_io(int old[2]);
int					save_io(int old[2], int new[2]);
int					set_io(int old[2]);
int					get_redir(t_exec *exec);
void				close_all(void);
void				close_fds(int fds[2]);
void				free_global(t_exec *exec, t_shell *shell);

int					ms_exec_bin(t_exec *exec, t_shell *shell);
int					execbin(t_exec *exec, t_shell *shell);

enum e_file_status	get_file_status(char *file);
char				*get_bin(char *cmd, t_env *env);

int					red_error(char *file);

#endif