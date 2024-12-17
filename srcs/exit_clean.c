#include "../minishell.h"

void	error_code(t_pipex *data)
{
	if (data)
	{
		free_struct(data);
		if (data->cur_env)
			free_list(data->cur_env);
		free(data);
	}
	exit(errno);
}

void exit_child(t_pipex *data, int index, int errnum)
{
	int pid[data->cmnd_count];
	int status;

	// printf("ERRRNUM: %d\n", errnum);
	pid[index] = fork();
	if (pid[index] == -1)
		return (perror("fork failed\n"), error_code(data));
	if (!pid[index])
		exit(errnum);
	else
	{
		if (waitpid(pid[index], &status, 0) == -1)
			return (perror("waitpid failed!"), error_code(data));
		data->exit_codes[index] = WEXITSTATUS(status);
	}
}
