/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 06:04:21 by gcros             #+#    #+#             */
/*   Updated: 2024/06/01 02:12:10 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "arr.h"

typedef struct s_pathexp
{
	int		dir;
	char 	**patterns;
	t_array	*files;
}	t_pathexp;

char	*ms_pathexp(char *pattern);
int		pattern_match(char *pattern, char *str);

#endif