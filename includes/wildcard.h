/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 06:04:21 by gcros             #+#    #+#             */
/*   Updated: 2024/05/21 10:32:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "arr.h"

typedef struct s_pattern
{
	t_array	*list;
	int		dir;
}	t_pattern;

char	*ms_pathexp(char *pattern);
int		pattern_match(char *pattern, char *str);

#endif