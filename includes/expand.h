/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:23:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/11 22:20:56 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"
# include "lexer.h"

// utils
t_command_type	ms_get_before_type_widlcard(t_array *array);
void			ms_append_new_command_int(t_array *new_array,
					int type, int content);
void			ms_append_env_to_last_command(t_array *new_array,
					char *env_str);
void			ms_append_new_command_str(t_array *new_array,
					int type, char *content);
char			*ms_get_exp(char *str, t_env *env);
char			*ms_get_last_char(char *str);
t_command		*ms_get_last_command(t_array *array);
t_command_type	ms_get_last_type(t_array *array);
t_array			*ms_initialize_new_array(t_shell *shell);
int				ms_is_last_type_text_or_expand(t_array *new_array);
void			ms_update_last_command_type(t_array *new_array,
					int type, char *str);

// handle
void			ms_handle_cmd_empty(t_array *new_array);
void			ms_handle_cmd_text(t_command *command,
					t_array *new_array);
void			ms_handle_cmd_expand_quote(t_command *command,
					t_array *new_array, t_shell *shell);
void			ms_handle_cmd_expand(t_command *command,
					t_array *new_array, t_shell *shell);
void			ms_handle_cmd_wildcard(t_array *new_array);

t_array			*ms_new_join(t_array *array, t_shell *shell);

#endif