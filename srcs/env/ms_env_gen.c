/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:15:41 by gcros             #+#    #+#             */
/*   Updated: 2024/06/12 19:23:36 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

static int	get_value(char *str, char **out);
static int	is_valid(char *var);

/**
 * @brief generate env tree from a char** NULL terminated type
 * 
 * @param strs the char** source
 * @param env the out tree
 * @return int the error output (0: ok, 1: error)
 */
int	ms_env_gen(char **strs, t_env **env)
{
	char	**p;
	t_env	*tmp;

	p = strs;
	while (*p != NULL)
	{
		tmp = NULL;
		if (ms_parse_env_node(*p, &tmp) == 0
			&& !(tmp->value == NULL && ms_env_exist(*env, tmp->key)))
			ms_env_add(env, tmp);
		p++;
	}
	if (*p == NULL)
		return (0);
	ms_env_collapse(env);
	return (1);
}

/**
 * @brief parse the node form a string
 * 
 * @param str the source string
 * @param out the out node 
 * @return int the error output (0: ok, 1: error)
 */
int	ms_parse_env_node(char *str, t_env **out)
{
	char	*s1;
	char	*s2;
	t_env	*e;

	s1 = NULL;
	s2 = NULL;
	*out = NULL;
	if (*str == '=' || get_key(str, &s1) == 1 || !is_valid(s1)
		|| get_value(str, &s2) == 1)
	{
		free(s1);
		free(s2);
		return (1);
	}
	e = ms_env_new(s1, s2);
	*out = e;
	if (e == NULL)
	{
		free(s1);
		free(s2);
	}
	return (e == NULL);
}

/**
 * @brief parse the key form a string
 * 
 * @param str the source string
 * @param out the out string
 * @return int the error output (0: ok, 1: error)
 */
int	get_key(char *str, char **out)
{
	char	*tmp;
	size_t	i;

	tmp = ft_strchr(str, '=');
	if (tmp == NULL)
	{
		*out = ft_strdup(str);
		return (*out == NULL);
	}
	i = tmp - str;
	tmp = malloc(i + 1);
	if (tmp != NULL)
		ft_strlcpy(tmp, str, i + 1);
	*out = tmp;
	return (*out == NULL);
}

/**
 * @brief parse the value form a string_env_node
 * 
 * @param str the source string
 * @param out the out string
 * @return int the error output (0: ok, 1: error)
 */
static int	get_value(char *str, char **out)
{
	*out = NULL;
	str = ft_strchr(str, '=');
	if (str == NULL)
		return (0);
	str += *str == '=';
	*out = ft_strdup(str);
	return (*out == NULL);
}

static int	is_valid(char *var)
{
	char	*c;

	if (var[0] <= '9' && var[0] >= '0')
		return (0);
	c = var;
	while (*c)
	{
		if (!(ft_isalnum(*c) || *c == '_'))
			return (0);
		c++;
	}
	return (1);
}
