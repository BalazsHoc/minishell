#include "../minishell.h"

void	error_code(t_pipex *data)
{
	if (data)
		free_struct(data);
	rl_clear_history();
	exit(errno);
}

void exit_child(t_pipex *data, int index_1, int index_2, int errnum)
{
	int status;

	data->pid[index_2] = fork();
	if (data->pid[index_2] == -1)
		return (perror("fork failed\n"), error_code(data));
	if (!data->pid[index_2])
	{
		errno = errnum;
		error_code(data);
	}
	else
	{
		if (waitpid(data->pid[index_2], &status, 0) == -1)
			return (perror("waitpid failed!"), error_code(data));
		data->lines[index_1]->exit_codes[index_2] = WEXITSTATUS(status);
		errno = WEXITSTATUS(status);
	}
}
