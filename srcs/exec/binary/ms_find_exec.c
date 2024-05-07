/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:10:46 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 02:27:44 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "str.h"
#include <unistd.h>

int	check_file(char *path, char *name, char **out);

/**
 * @brief search and expend file name with the env path
 * 
 * @param cmd the command to search
 * @param env_path string with paths split with ':'
 * @param out the full path of the command
 * @return int the error (0: found, 1: not found, -1: error)
 */
int	ms_find_exec(char *cmd, char *env_path, char **out)
{
	char	**paths;
	char	**ptr;
	int		ret;

	*out = NULL;
	ret = 0;
	if (env_path == NULL || cmd == NULL || *cmd == '\0')
		return (1);
	paths = ft_split(env_path, ':');
	if (paths == NULL)
		return (-1);
	ptr = paths - 1;
	while (*++ptr != NULL)
	{
		ret = check_file(*ptr, cmd, out);
		if (ret != 0)
			break ;
	}
	if (ret != -1)
		ret = (*ptr == NULL);
	ft_strsfree(paths);
	return (ret);
}

/**
 * @brief check the command accessibility (exist and is exec)
 * 
 * @param path path
 * @param name command name
 * @param out change if can exist
 * @return int 0 if not executable, 1 if executable
 */
int	check_file(char *path, char *name, char **out)
{
	char	*file;

	file = ft_strsjoin((char *[]){path, "/", name, NULL});
	if (file == NULL)
		return (-1);
	if (is_file(file))
	{
		*out = file;
		if (is_exec(file))
			return (1);
	}
	free(file);
	return (0);
}
