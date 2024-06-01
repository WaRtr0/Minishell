/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pathexp_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:52:54 by gcros             #+#    #+#             */
/*   Updated: 2024/06/01 02:11:35 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr.h"
#include "str.h"
#include "wildcard.h"
#include <sys/types.h>
#include <dirent.h>
#include "exec.h"
#include "utils.h"

int		req_list(int lvl, t_pathexp *pathexp, char *path);
char	*get_files(char **strs, int dir);

char	*ms_pathexp(char *pattern)
{
	char		*str;
	t_pathexp	pathexp;

	pathexp.files = ft_arr_new(20);
	if (pathexp.files == NULL)
		return (NULL);
	pathexp.dir = pattern[ft_strlen(pattern) - 1] == '/';
	pathexp.patterns = ft_split(pattern, '/');
	str = NULL;
	if (pathexp.patterns != NULL)
	{
		req_list(0, &pathexp, ".");
		if (pathexp.files->size == 0)
			str = ft_strdup(pattern);
		else if (ft_arr_append(pathexp.files, NULL))
			str = get_files((char **)pathexp.files->data, pathexp.dir);
	}
	ft_strsfree(pathexp.patterns);
	ft_arr_free(&pathexp.files, free);
	return (str);
}

char	*get_path(char *path, char *file, int lvl)
{
	char	*str;

	if (lvl == 0 && *path == '.')
		str = ft_strdup(file);
	else
		str = ft_strjoin_seperator(path, file, "/");
	return (str);
}

char	*get_files(char **strs, int dir)
{
	char	*str;
	char	*p;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	str = malloc(count + 1 + i + dir * count);
	if (!str)
		return (NULL);
	i = 0;
	p = str;
	while (strs[i])
	{
		p = ft_stpcpy(p, strs[i++]);
		if (dir)
			*(p++) = '/';
		*(p++) = ' ';
	}
	*(p) = '\0';
	return (str);
}

int	is_valide_file(char *file, char *pattern)
{
	(void) pattern;
	(void) file;
	if (ft_strncmp(file, ".", 2) == 0 && ft_strncmp(file, pattern, 2) != 0)
		return (0);
	if (ft_strncmp(file, "..", 3) == 0 && ft_strncmp(file, pattern, 3) != 0)
		return (0);
	if (!(pattern_match(pattern, file) == 0))
		return (0);
	return (1);
}

int	req_list(int lvl, t_pathexp *pathexp, char *path)
{
	DIR				*dp;
	struct dirent	*ep;
	char			*str;

	if (pathexp->patterns[lvl] == NULL && path != NULL)
		if ((pathexp->dir && !(get_status(path) & fs_is_dir))
			|| ft_arr_append(pathexp->files, path) == 0)
			return (1);
	if (pathexp->patterns[lvl] == NULL || path == NULL)
		return (0);
	dp = opendir(path);
	ep = readdir(dp);
	while (dp != NULL && ep != NULL)
	{
		if (is_valide_file(ep->d_name, pathexp->patterns[lvl]))
		{
			str = get_path(path, ep->d_name, lvl);
			if (req_list(lvl + 1, pathexp, str) == 1)
				free(str);
		}
		ep = readdir(dp);
	}
	closedir(dp);
	return (0);
}
