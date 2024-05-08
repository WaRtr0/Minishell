/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_acces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:54:59 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 04:05:20 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <unistd.h>

/**
 * @brief check if file exist
 * 
 * @param path the path of the file
 * @return int (1 if ok, 0 else)
 */
int	is_file(char *path)
{
	return (access(path, F_OK) == 0);
}

/**
 * @brief check if file is executable
 * 
 * @param path the path of the file
 * @return int (1 if ok, 0 else)
 */
int	is_exec(char *path)
{
	return (access(path, X_OK) == 0);
}

/**
 * @brief check if file readable
 * 
 * @param path the path of the file
 * @return int (1 if ok, 0 else)
 */
int	can_read(char *path)
{
	return (access(path, R_OK) == 0);
}

/**
 * @brief check if file is writable
 * 
 * @param path the path of the file
 * @return int (1 if ok, 0 else)
 */
int	can_write(char *path)
{
	return (access(path, W_OK) == 0);
}
