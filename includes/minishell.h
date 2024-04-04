/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wartro <wartro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:19:27 by wartro            #+#    #+#             */
/*   Updated: 2024/04/04 23:54:23 by wartro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#  define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
// for malloc
# include <sys/types.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
    char	*truc;
}	t_shell;

int main(int argc, char **argv, char **envp);

#endif