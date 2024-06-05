/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pathexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:52:54 by gcros             #+#    #+#             */
/*   Updated: 2024/06/05 17:41:39 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr.h"
#include "str.h"
#include "wildcard.h"
#include <sys/types.h>
#include <dirent.h>
#include "exec.h"
#include "utils.h"
#include "put.h"

int		req_list(int lvl, t_pathexp *pathexp, char *path);

t_array	*ms_pathexp(char *pattern)
{
	t_pathexp	pathexp;

	pathexp.files = ft_arr_new(20);
	pathexp.pattern = pattern;
	if (pathexp.files == NULL)
		return (NULL);
	pathexp.dir = pattern[ft_strlen(pattern) - 1] == '/';
	pathexp.patterns = ft_split(pattern, '/');
	if (pathexp.patterns != NULL)
	{
		if (pattern[0] == '/')
			req_list(0, &pathexp, "/");
		else
			req_list(0, &pathexp, ".");
		exp_get_files(&pathexp, pathexp.dir);
	}
	ft_strsfree(pathexp.patterns);
	//for (size_t i = 0; i < pathexp.files->size; i++)
	//	ft_putendl_fd(pathexp.files->data[i], 1);
	return (pathexp.files);
}

char	*get_path(char *path, char *file, int lvl)
{
	char	*str;

	if (lvl == 0 && (*path == '.'))
		str = ft_strdup(file);
	else if (lvl == 0 && (*path == '/'))
		str = ft_strjoin_seperator(path, file, "");
	else
		str = ft_strjoin_seperator(path, file, "/");
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
	ep = NULL + 1;
	while (dp != NULL && ep != NULL)
	{
		ep = readdir(dp);
		if (ep != NULL && is_valide_file(ep->d_name, pathexp->patterns[lvl]))
		{
			str = get_path(path, ep->d_name, lvl);
			if (req_list(lvl + 1, pathexp, str) == 1)
				free(str);
		}
	}
	if (dp != NULL)
		closedir(dp);
	return (0);
}
