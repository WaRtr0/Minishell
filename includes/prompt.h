/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wartro <wartro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/04/04 20:53:09 by wartro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int	loop(int ac, char **av, char **env);

#endif