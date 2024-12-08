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
	rl_clear_history();
	exit(errno);
}

void exit_child(t_pipex *data)
{
	int pid;
	int status;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed\n"), error_code(data));
	if (!pid)
		exit(errno);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (perror("waitpid failed!"), error_code(data));
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else
			return (perror("Child did not terminate properly!"), error_code(data));
	}
}
