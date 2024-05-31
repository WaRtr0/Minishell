
static	int	pipe_run(t_pipe_run *run, t_shell *shell)
{
	t_command	*command;

	command = (t_command *)run->array->data[run->index];
	pipe_input(run);
	if (command->type == CMD_JOIN)
		join_part(command->content.array, shell,
			(int [2]){run->tmp_fd[0], run->tmp_fd[1]});
	else if (command->type == CMD_PARENTHESIS)
		pare_part(run->array, shell,
			(int [2]){run->tmp_fd[0], run->tmp_fd[1]}, run->index);
	if (run->tmp_fd[0] != -1 && (run->tmp_fd[0] | 1) != 1)   //voir
		close(run->tmp_fd[0]);  //voir
	if (run->index < run->array->size - 1)
	{
		close(run->pipe_fd[1]);
		run->tmp_fd[0] = run->pipe_fd[0];
	}
	run->index++;
	return (0);
}

int	ms_handle_pipe(t_array *array, t_shell *shell, int fd[2])
{
	t_pipe_run	run;
	int			ret;
	int			tmp;

	run.tmp_fd[0] = fd[0];
	run.fd[0] = fd[0];
	run.fd[1] = fd[1];
	run.pipe_fd[0] = -1;
	run.pipe_fd[1] = -1;
	run.array = array;
	shell->arb_pipe++;
	if (!shell->prompt_listen)
		return (0);
	run.index = 0;
	ret = 0;
	while (run.index < array->size)
		pipe_run(&run, shell);
	while (wait(&tmp) != -1)
		ret = tmp;
	ms_set_status(ret);
	shell->in_pipe--;
	return (0);
}

static	int	join_part(t_array *array, t_shell *shell, int fd[2])
{
	shell->in_pipe = 1;
	return (ms_handle_join(array, shell, fd));
}


static	int	pipe_input(t_pipe_run *run)
{
	if (run->index < run->array->size - 1)
	{
		if (pipe(run->pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		run->tmp_fd[1] = run->pipe_fd[1];
	}
	else
	{
		run->tmp_fd[1] = run->fd[1];
	}
	return (0);
}