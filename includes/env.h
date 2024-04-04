/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/04/04 01:24:31 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "list.h"

typedef struct s_env
{
	char	*tok;
	t_env	*left;
	t_env	*right;
}	t_env;



#endif