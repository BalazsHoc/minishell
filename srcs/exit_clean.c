#include "../minishell.h"

void	error_code(t_pipex *data, char *line)
{
	if (!data)
		return (free(line));
	free_a(line, data);
	exit(EXIT_FAILURE);
}

void exit_child(int errnum, char *line, t_pipex *data)
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed\n");
		error_code(data, line);
	}
	if (!pid)
		exit(errnum);
	else
		wait(NULL);
}