/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:14:24 by gcros             #+#    #+#             */
/*   Updated: 2024/06/07 19:03:53 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str.h"
#include "wildcard.h"

void	swap(void **p1, void **p2);
void	sort_files(t_array *files);
void	to_dir(t_array *files);

void	exp_get_files(t_pathexp *pathexp, int dir)
{
	char	*tmp;

	if (pathexp->files->size == 0)
	{
		tmp = ft_strdup(pathexp->pattern);
		if (tmp != NULL)
			ft_arr_append(pathexp->files, tmp);
		else
			write(2, "la\n", 3);
		return ;
	}
	sort_files(pathexp->files);
	if (dir)
		to_dir(pathexp->files);
}

void	to_dir(t_array *files)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (i < files->size)
	{
		tmp = ft_strjoin(files->data[i], "/");
		if (tmp == NULL)
			continue ;
		swap(files->data + i, (void **)&tmp);
		free(tmp);
		i++;
	}
}

void	swap(void **p1, void **p2)
{
	char	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	sort_files(t_array *files)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < files->size)
	{
		j = i;
		while (j > 0 && ft_strncmp(files->data[j - 1] + (((char *)files->data[j - 1])[0] == '.'), files->data[j] + (((char *)files->data[j])[0] == '.'), -1) > 0)
		{
			swap(files->data + j, files->data + j - 1);
			j--;
		}
		i++;
	}
}
