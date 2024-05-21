/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:56 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/21 09:50:43 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "lexer.h"
#include "utils.h"
#include "env.h"
#include "exec.h"
#include "handle.h"


int	ms_handle_pipe(t_array *array, t_shell *shell, int fd[2])
{
	size_t		i;
	t_command	*command;
	int			pipe_fd[2];
	int			temp_fd[2];
	int			t_fd[2];
	pid_t pid;

	temp_fd[0] = fd[0];
	shell->arb_pipe++;
	if (!shell->prompt_listen)
		return (0);
	printf("PIPE... [%d]\n", shell->in_pipe);

	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];

		 if (i < array->size - 1)
		 {
            if (pipe(pipe_fd) == -1)
			{
                perror("pipe");
                return (1);
            }
			temp_fd[1] = pipe_fd[1];
        }
		else
			temp_fd[1] = fd[1];

		if (command->type == CMD_JOIN)
		{
			shell->in_pipe = 1;
			ms_handle_join(command->content.array, shell, (int [2]){temp_fd[0], temp_fd[1]});
		}
		else if (command->type == CMD_PARENTHESIS)
		{
			t_fd[0] = temp_fd[0];
			t_fd[1] = temp_fd[1];
			if (i + 1 < array->size)
			{
				command = (t_command *)array->data[i + 1];
				if (command->type == CMD_JOIN_NO_PRINT)
					ms_get_fd(command->content.array, shell, t_fd);
				command = (t_command *)array->data[i];
			}
			// ms_handle(command->content.array, shell, t_fd); #grosse erreur MDR

			pid = fork();
			if (pid == 0)
			{
				ms_handle(command->content.array, shell, (int [2]){t_fd[0], t_fd[1]});
				exit(0);
			}
			else if (pid < 0)
			{
				perror("fork");
				return (1);
			}
		}

		if (i < array->size - 1)
		{
			close(pipe_fd[1]);
			temp_fd[0] = pipe_fd[0];
		}
		i++;
	}
	while (wait(NULL) != -1)
		(void) "todo";
	//wait => attente que tout les programmes ce termine
	shell->in_pipe--;
	return (0);
}
