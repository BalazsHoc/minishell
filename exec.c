#include "minishell.h"

char *join_this(char *s1, char *s2)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!s2)
        return (free_str(s1), NULL);
    while (s1 && s1[i])
        i++;
    while (s2 && s2[j])
        j++;
    if (i + j == 0)
        return (NULL);
    new = malloc(sizeof(char) * (i + j + 1));
    if (!new)
        return (free_str(s1), NULL);
    new[i + j] = 0;
    i = 0;
    while (s1 && s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2 && s2[j])
        new[i++] = s2[j++];
    free_str(s1);
    return (new);
}

void exec_cmnd(t_pipex *data, int index, int cmnd_count, int (*pipes)[2])
{
    int pid;
    int i;

	pid = fork();
	if (pid < 0)
        return (error_code(data, NULL, 1, 1));
	else if (pid == 0)  // CHILD
    { 
        if (index > 0 && dup2(pipes[index - 1][0], STDIN_FILENO) == -1)
            return (printf("error dup2\n"), error_code(data, NULL, 1, 0));
        else if (data->fd == -2 && index < cmnd_count -1 && dup2(pipes[index][1], STDOUT_FILENO) == -1)
            return (printf("dup2"), error_code(data, NULL, 1, 0));
        else if (data->fd != -2 && dup2(data->fd, STDOUT_FILENO) == -1)
            return (printf("dup2"), error_code(data, NULL, 1, 0));
        i = -1;
        while (++i < cmnd_count - 1)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        return (execve(data->paths[index], data->ops[index], NULL),
            perror("execve"), error_code(data, NULL, 1, 0));
    }
}

void exec_mini(t_pipex *data, int index, int cmnd_count, int (*pipes)[2])
{
    int pid;
    int i;

	pid = fork();
	if (pid < 0)
        return (error_code(data, NULL, 1, 1));
	else if (pid == 0)  // CHILD
    { 
        if (index > 0 && dup2(pipes[index - 1][0], STDIN_FILENO) == -1)
            return (printf("error dup2\n"), error_code(data, NULL, 1, 0));
        else if (data->fd == -2 && index < cmnd_count -1 && dup2(pipes[index][1], STDOUT_FILENO) == -1)
            return (printf("dup2"), error_code(data, NULL, 1, 0));
        else if (data->fd != -2 && dup2(data->fd, STDOUT_FILENO) == -1)
            return (printf("dup2"), error_code(data, NULL, 1, 0));
        i = -1;
        while (++i < cmnd_count - 1)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        return (mini_commands(data, index), error_code(data, NULL, 1, 0));
    }
}

