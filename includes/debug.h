/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:10:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 20:44:01 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"
# include "lexer.h"
# include "conf.h"
# include <stdint.h>

char	*ms_debug_cmd_to_str(t_command_type type);
void	ms_debug_command_to_json(int indent, t_array *array);
void	*ms_debug_print_json(t_command *command);
void	ms_debug_command_map(t_array *array, void *(*f)(void *));
int		ms_debug(t_shell *shell);

#endif