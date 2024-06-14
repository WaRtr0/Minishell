/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:14:08 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 16:51:18 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "str.h"
# include "unistd.h"
# include "stdlib.h"

int		free_commands(t_array *array);
char	*ft_select_str(char *str, size_t n);
int		ft_include(char const *str, char c);
char	**ft_split_chars(char const *s, char *c);
char	*ft_strjoin_seperator(char *s1, char *s2, char *sep);
int		free_commands_handle(t_array *array);

#endif