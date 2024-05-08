/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:50:41 by gcros             #+#    #+#             */
/*   Updated: 2024/05/07 01:05:48 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int		ms_exec(t_exec *exec, t_shell *shell);
int		ms_find_exec(char *name, char *path, char **out);
int		is_file(char *path);
int		is_exec(char *path);
int		can_read(char *path);
int		can_write(char *path);
char	*ms_get_exec_name(char *name, char *path);

int		ms_run_builtin(t_exec *exec, t_shell *shell);
int		ms_exec_builtin(t_exec *exec, t_shell *shell);

int		restore_io(int old[2]);
int		save_io(int old[2], int new[2]);
int		set_io(int old[2]);

#endif