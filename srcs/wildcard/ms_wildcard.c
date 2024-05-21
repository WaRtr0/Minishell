/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:03:07 by gcros             #+#    #+#             */
/*   Updated: 2024/05/21 15:12:20 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr.h"
#include "str.h"
#include "wildcard.h"
#include <sys/types.h>
#include <dirent.h>
#include "exec.h"

int	add_file(t_pattern	*pattern_ptr, char	*pattern, struct dirent	*ep);
int	list_file(t_pattern	*pattern_ptr, char	*pattern);

char	*ms_pathexp(char *pattern)
{
	t_pattern	pattern_ptr;
	char		*str;

	str = NULL;
	pattern_ptr.list = ft_arr_new(10);
	pattern_ptr.dir = pattern[ft_strlen(pattern) - 1] == '/';
	if (pattern_ptr.dir)
		pattern[ft_strlen(pattern) - 1] = '\0';
	if (pattern_ptr.list == NULL)
	{
		ft_arr_free(&pattern_ptr.list, free);
		return (NULL);
	}
	list_file(&pattern_ptr, pattern);
	if (pattern_ptr.list->size == 0)
		str = ft_strdup(pattern);
	else if (ft_arr_append(pattern_ptr.list, NULL))
		str = ft_strsjoin((char **)pattern_ptr.list->data);
	ft_arr_free(&pattern_ptr.list, free);
	return (str);
}

int	list_file(t_pattern	*pattern_ptr, char	*pattern)
{
	DIR				*dp;
	struct dirent	*ep;
	char			*str;

	dp = opendir("./");
	if (dp == NULL)
		return (0);
	ep = readdir(dp);
	while (ep != NULL)
	{
		str = NULL;
		if (add_file(pattern_ptr, pattern, ep))
			str = ft_strdup(" ");
		if (str != NULL)
			ft_arr_append(pattern_ptr->list, str);
		ep = readdir(dp);
	}
	closedir(dp);
	return (0);
}

int	add_dir(t_pattern	*pattern_ptr, struct dirent *ep)
{
	char	*str;

	if ((get_status(ep->d_name) & fs_is_dir) == 0)
		return (0);
	str = ft_strdup(ep->d_name);
	if (str != NULL)
		ft_arr_append(pattern_ptr->list, str);
	return (1);
}

int	add_file(t_pattern	*pattern_ptr, char	*pattern, struct dirent *ep)
{
	char	*str;

	if (pattern_match(pattern, ep->d_name))
		return (0);
	if (pattern_ptr->dir)
		return (add_dir(pattern_ptr, ep));
	str = ft_strdup(ep->d_name);
	if (str != NULL)
		ft_arr_append(pattern_ptr->list, str);
	return (1);
}

