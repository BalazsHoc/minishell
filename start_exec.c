#include "minishell.h"

int free_this(char *s)
{
    if (s)
        free(s);
    return (1);
}

int is_red_inline(t_pipex *data, int index)
{
    int i;
    int check;

    i = -1;
    check = -1;
    while (data->cmnds[index] && data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2))
            check = i;
        if (!ft_strncmp(data->cmnds[index][i], "<<", 3))
            check = i;
    }
    return (check);
}

int is_in_inline(t_pipex *data, int index)
{// is  a single redirection in the line? 
    int i;
    int check;

    i = -1;
    check = -1;
    while (data->cmnds[index] && data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2))
            check = i;
    }
    return (check);
}

char *replace_nl(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '\n')
            str[i] = 0;
    }
    return (str);
}

int is_valid_in(t_pipex *data, int index)
{
    int i;
    int fd;

    i = -1;
    fd = -1;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2) && data->cmnds[index][i + 1])
        {
            if (fd > 0)
                close(fd);
            fd = open(data->cmnds[index][i + 1], O_RDONLY);
            if (fd == -1)
                return (0);
        }
    }
    if (fd > 0)
        close(fd);
    return (fd);
}

int first_invalid_in(t_pipex *data, int index)
{
    int i;
    int fd;

    i = -1;
    fd = -1;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2) && data->cmnds[index][i + 1])
        {
            if (fd > 0)
                close(fd);
            fd = open(data->cmnds[index][i + 1], O_RDONLY);
            if (fd == -1)
                return (i + 1);
        }
    }
    if (fd > 0)
        close(fd);
    return (0);
}

int first_invalid_out(t_pipex *data, int index)
{
    int i;
    int fd;

    i = -1;
    fd = -1;
    while (data->cmnds[index][++i])
    {
        if ((!ft_strncmp(data->cmnds[index][i], ">>", 3) || !ft_strncmp(data->cmnds[index][i], ">", 2))
            && data->cmnds[index][i + 1])
        {
            if (fd > 0)
                close(fd);
            fd = open(data->cmnds[index][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (i + 1);
        }
    }
    if (fd > 0)
        close(fd);
    return (i);
}


int open_out(t_pipex *data, int index)
{
    int i;
    int fd;

    i = -1;
    fd = 0;
    if (!is_valid_in(data, index) && first_invalid_in(data, index) < first_invalid_out(data, index))
        return (1);
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], ">>", 3)
            || !ft_strncmp(data->cmnds[index][i], ">", 2))
            {
                if (fd)
                    close(fd);
                if (!ft_strncmp(data->cmnds[index][i], ">>", 3))
                    fd = open(data->cmnds[index][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                else
                    fd = open(data->cmnds[index][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    return (printf("bash: %s: %s\n", data->cmnds[index][i + 1], strerror(errno)), exit_child(data, index, 1), -1);
            }
    }
    return (fd);
}

void start_exec(t_pipex *data)
{
    int     i;
    int     status;
    int     pipes[MAX_CMNDS -1][2];
    pid_t   pid[data->cmnd_count];

    i = -1;
    create_pipes(pipes, data->cmnd_count);
    // signal(SIGCHLD, SIG_IGN);
    while (data->cmnds[++i] && here_doc(data, i))
    {
        data->fd_out = open_out(data, i);
        if (ft_strncmp(data->paths[i], "pathnfound", 11)
            && is_valid_in(data, i) && data->fd_out >= 0 && data->ops[i][0][0])
        {
            if (is_red_inline(data, i) >= 0 && !ft_strncmp(data->cmnds[i][is_red_inline(data, i)], "<<", 3) && free_this(data->input))
            {
                data->input = get_input(data, i, is_red_inline(data, i));
                // printf("INPUT: %s$\n", data->input);
            }
            if (!ft_strncmp(data->paths[i], "minicmnds", 11))
               exec_mini(data, i, pipes);
            else
                exec_cmnd(data, i, pipes, pid);
            // printf("_________________________________________________________________________________________\n");
        }
        else if (!is_valid_in(data, i) && !data->exit_codes[i])
        {
            printf("bash: %s: No such file or directory\n", data->cmnds[i][first_invalid_in(data, i)]);
            exit_child(data, i, 1);
        }
        else if (!ft_strncmp(data->paths[i], "pathnfound", 11) && data->ops[i][0] && !data->exit_codes[i])
        {
            printf("bash: command not found %s\n", data->ops[i][0]);
            exit_child(data, i , 127);
        }
        if (data->fd_out > 2)
            close(data->fd_out);
        // printf("EXIT\n");
    }
    close_pipes(pipes, data->cmnd_count);
    i = -1;
    while (++i < data->cmnd_count)
    {
        if (!data->exit_codes[i])
        {
            waitpid(pid[i], &status, 0);
            if (WIFEXITED(status))
                data->exit_codes[i] = WEXITSTATUS(status);
        }
    }
    // printf("LAST1: %d\n", data->exit_codes[data->cmnd_count - 1]);
    // exit_child(data, data->cmnd_count - 1, data->exit_codes[data->cmnd_count - 1]);
    // printf("LAST2: %d\n", data->exit_codes[data->cmnd_count - 1]);
}
