#include "../minishell.h"

// overwritten with checks and the ex flag is for if it should exit or not
void	error_code(t_pipex *data, char *line, int ex)
{
	if (!data && !ex)
	{
		if (line)
			free(line);
		return ;
	}
	if (!data && ex)
	{
		if (line)
			free(line);
		exit(EXIT_FAILURE);
	}
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
		error_code(data, line, 1);
	}
	if (!pid)
		exit(errnum);
	else
		wait(NULL);
}
