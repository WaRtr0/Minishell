/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:23:19 by gcros             #+#    #+#             */
/*   Updated: 2024/06/14 17:14:22 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>
#include <fcntl.h>

enum e_file_status	get_file_status(char *file)
{
	struct stat			st;
	enum e_file_status	r;

	if (stat(file, &st) < 0)
		return (fs_default);
	r = fs_exist;
	if (S_ISDIR(st.st_mode))
		return (r | fs_is_dir);
	if (access(file, X_OK) == 0)
		r |= fs_exec;
	if (access(file, R_OK) == 0)
		r |= fs_read;
	if (access(file, W_OK) == 0)
		r |= fs_write;
	return (r);
}
