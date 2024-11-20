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
    // printf("RED_INLINE: %d\n", check);
    while (data->cmnds[index] && data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2)
            || !ft_strncmp(data->cmnds[index][i], "<<", 3))
            check = i;
    }
    // printf("RED_INLINE: %d\n", check);
    return (check);
}

int is_in_inline(t_pipex *data, int index)
{
    int i;
    int check;

    i = -1;
    check = -1;
    while (data->cmnds[index] && data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2))
            check = i;
    }
    printf("RETURN INLINE: %d\n", check);
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

char *get_input(t_pipex *data, int index_1, int index_2)
{
    int fd;
    char *buf;
    char *key;
    char *input;

    key = data->cmnds[index_1][index_2 + 1];
    // printf("KEY%s\n", key);
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<", 2))
    {
        fd = open(key, O_RDONLY);   
        if (fd == -1)
            return (printf("bash: %s: no such file or directory\n", key), NULL);
    }
    else
        fd = 0;
    buf = get_next_line(fd, 0);
    input = NULL;
    // printf("BUF: %s\n", buf);
    while (buf && (fd > 2 || (fd == 0 && !ft_strcmp_2(buf, key))))
    {
        input = join_this(input, buf);
        free(buf);
        buf = get_next_line(fd, 0);
        // printf("THIS: %s$\n", buf);
    }
    free_str(buf);
    // printf("INPUT: %s$\n", input);
    if (fd > 2)
        close(fd);
    return (input);
}

int is_valid_in(t_pipex *data, int index)
{
    int i;
    int fd;
    char *infile;

    i = -1;
    infile = NULL;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2))
            infile = data->cmnds[index][i + 1];
    }
    if (!infile)
        return (0);
    fd = open(infile, O_RDONLY);
    if (fd == -1)
        return (0);
    printf("VALID IN!!!\n");
    return (close(fd), 1);
}

int open_out(t_pipex *data, int index)
{
    int i;
    int fd;
    int check;
    char *outfile;

    i = -1;
    outfile = NULL;
    check = 0;
    fd = 0;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], ">>", 3)
            || !ft_strncmp(data->cmnds[index][i], ">", 2))
            {
                if (fd)
                    close(fd);
                outfile = data->cmnds[index][i + 1];
                fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
        if (!ft_strncmp(data->cmnds[index][i], "<<", 3))
            check = 1;
    }
    if (!outfile)
        return (-2);
    if (check)
        fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else 
        fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        printf("ERRNO: %d", errno);
    return (fd);
}

// void start_exec(t_pipex *data, int cmnd_count)
// {
//     int     i;
//     int     fd;
    
//     i = -1;
//     data->input = NULL;
//     while (data->cmnds[++i] && data->cmnds[i] && here_doc(data, i))
//     {
//         if (i > 10)
//             break;
//         fd = open_out(data, i);
//         // data->input 
//         if (ft_strncmp(data->paths[i], "pathnfound", 11)
//             && (is_valid_in(data, i)
//             || (!is_valid_in(data, i) && is_in_inline(data, i) == -1)))
//         {
//             if ((is_valid_in(data, i) || (!is_valid_in(data, i) && is_red_inline(data, i) != -1)) && free_this(data->input))
//                 data->input = get_input(data, i, is_red_inline(data, i));
//             printf("INPUT: %s$\n", data->input);
//             if (!ft_strncmp(data->paths[i], "minicmnds", 11))
//                mini_commands(data, i);
//             else 
//                 exec_cmnd(data, i);
//             printf("EXECCMND FINISHED!\n");
//             printf("_________________________________________________________________________________________\n");
//             if (fd != -2)
//                 write(open_out(data, i), data->input, ft_strlen(data->input));
//             else if (!data->cmnds[i + 1])
//                 write(1, data->input, ft_strlen(data->input));
//             printf("_________________________________________________________________________________________\n");
//         }
//         else if (ft_strncmp(data->paths[i], "pathnfound", 11) 
//             && (is_valid_in(data, i) || (!is_valid_in(data, i) && is_red_inline(data, i) != -1)))
//             printf("BASH: %s: no such file or directory\n", data->cmnds[i][is_red_inline(data, i) + 1]);
//         if (fd > 2)
//             close(fd);
//         printf("EXIT\n");
//     }
// }
void start_exec(t_pipex *data, int cmnd_count)
{
    int     i;
    int     pipes[MAX_CMNDS -1][2];

    i = -1;
    while (++i < cmnd_count)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }
    i = -1;
    data->input = NULL;
    // signal(SIGCHLD, SIG_IGN);
    while (data->cmnds[++i] && data->cmnds[i] && here_doc(data, i))
    {
        data->fd = open_out(data, i);
        // data->input 
        if (ft_strncmp(data->paths[i], "pathnfound", 11)
            && (is_valid_in(data, i)
            || (!is_valid_in(data, i) && is_in_inline(data, i) == -1)))
        {
            if ((is_valid_in(data, i) || (!is_valid_in(data, i) && is_red_inline(data, i) != -1)) && free_this(data->input))
                data->input = get_input(data, i, is_red_inline(data, i));
            printf("INPUT: %s$\n", data->input);
            if (!ft_strncmp(data->paths[i], "minicmnds", 11))
               exec_mini(data, i, cmnd_count, pipes);
            else 
                exec_cmnd(data, i, cmnd_count, pipes);
            printf("EXECCMND FINISHED!\n");
            printf("_________________________________________________________________________________________\n");
            if (data->fd != -2)
                write(open_out(data, i), data->input, ft_strlen(data->input));
            else if (!data->cmnds[i + 1])
                write(1, data->input, ft_strlen(data->input));
            printf("_________________________________________________________________________________________\n");
        }
        else if (ft_strncmp(data->paths[i], "pathnfound", 11) 
            && (is_valid_in(data, i) || (!is_valid_in(data, i) && is_red_inline(data, i) != -1)))
            printf("BASH: %s: no such file or directory\n", data->cmnds[i][is_red_inline(data, i) + 1]);
        if (data->fd > 2)
            close(data->fd);
        printf("EXIT\n");
    }
    for (i = 0; i < cmnd_count - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    while (wait(NULL) > 0);
}