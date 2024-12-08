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

// void	handle_pwd_tmp(t_pipex *data, int index)
// {
// 	while (!is_valid_cwd(data))
// 		chdir("..");
// 	data->tmp = create_tmp(data, index, "tmp_", 0);
// }

void    handle_child(t_pipex *data, int index, int(*pipes)[2], int cmnd_count, int fd)
{
    if (is_red_inline(data, index) != -1
        && !ft_strncmp(data->cmnds[index][is_red_inline(data, index)], "<", 2)) // if its simple infile
    {
        fd = open(data->cmnds[index][is_red_inline(data, index) + 1], O_RDONLY);
        if (fd == -1)
            return (printf("error open\n"), error_code(data));
    }
    if (!fd && index > 0 && dup2(pipes[index][0], STDIN_FILENO) == -1)
        return (printf("error dup2\n"), error_code(data));
    // else if (index == 0 && !fd && data->input && dup2(pipes[index - 1][0], STDIN_FILENO) == -1)
    //     return (printf("error dup2\n"), error_code(data, NULL, 1, 0));
    else if (fd && dup2(fd, STDIN_FILENO) == -1)
        return (printf("error dup2\n"), error_code(data));
    if (data->fd_out == -2 && index < cmnd_count - 1 && dup2(pipes[index + 1][1], STDOUT_FILENO) == -1)
        return (printf("dup2"), error_code(data));
    else if (data->fd_out != -2 && dup2(data->fd_out, STDOUT_FILENO) == -1)
        return (printf("dup2"), error_code(data));
    if (fd)
        close(fd);
    close_pipes(pipes, cmnd_count);
    if (!(data->cmnds[index + 1] && is_red_inline(data, index + 1) != -1
        && ft_strncmp(data->cmnds[index][is_red_inline(data, index + 1)], "<<", 3)))
        return (execve(data->paths[index], data->ops[index], NULL),
            perror("execve"), error_code(data));
    exit(EXIT_SUCCESS);
}

void exec_cmnd(t_pipex *data, int index, int cmnd_count, int (*pipes)[2])
{
    int pid;

    // printf("exec_cmnd\n");
    signal_change(data, 2);
    pid = fork();
	if (pid < 0)
        return (error_code(data));
	else if (!pid)
        handle_child(data, index, pipes, cmnd_count, 0);
}

void exec_mini(t_pipex *data, int index, int cmnd_count, int (*pipes)[2])
{
    int pid;
    int i;

    // printf("exec_mini\n");
	pid = fork();
	if (pid < 0)
        return (error_code(data));
	else if (pid == 0)  // CHILD
    { 
        if (data->fd_out == -2 && index < cmnd_count -1 && dup2(pipes[index + 1][1], STDOUT_FILENO) == -1)
            return (printf("dup2"), error_code(data));
        else if (data->fd_out != -2 && dup2(data->fd_out, STDOUT_FILENO) == -1)
            return (printf("dup2"), error_code(data));
        i = -1;
        while (++i < cmnd_count)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        return (mini_child(data, index), error_code(data));
    }
    else
        mini_commands(data, index);
}

