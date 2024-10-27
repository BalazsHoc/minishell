#include "../minishell.h"

void	error_code(t_pipex *data, char *line, int ex)
{
	if (ex)
	{
		if (data && line)
			free_a(line, data);
		else if (line)
			free(line);
		else if (data)
			free_struct(data);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (data && line)
			free_a(line, data);
		else if (line)
			free(line);
		else if (data)
			free_struct(data);
	}
}

void exit_child(int errnum, char *line, t_pipex *data)
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed\n");
		error_code(data, line, 1);
	}
	if (!pid)
		exit(errnum);
	else
		wait(NULL);
}
