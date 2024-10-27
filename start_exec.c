#include "minishell.h"

char *get_in(t_pipex *data, int index)
{
    int i;
    int fd;
    char *infile;
    char *buf;

    i = -1;
    infile = NULL;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2))
            infile = data->cmnds[index][i + 1];
    }
    if (!infile)
        return (NULL);
    fd = open(infile, O_RDONLY);
    if (fd == -1)
        printf("ERRNO: %d", errno);
    buf = get_next_line(fd, 0);
    infile = NULL;
    while (buf)
    {
        infile = ft_strjoin(infile, buf);
        free(buf);
        buf = get_next_line(fd, 0);
    }
    return (close(fd), infile);
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
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], ">>", 3)
            || !ft_strncmp(data->cmnds[index][i], ">", 2))
            outfile = data->cmnds[index][i + 1];
        if (!ft_strncmp(data->cmnds[index][i], "<<", 3))
            check = 1;
    }
    if (!outfile)
        return (1);
    if (check)
        fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else 
        fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        printf("ERRNO: %d", errno);
    return (fd);
}

void start_exec(t_pipex *data, int cmnd_count)
{
    int     i;
    
    i = -1;
    data->input = ft_calloc(sizeof(char *), (cmnd_count + 1));
    if (!data->input)
        return (error_code(data, NULL, 1));
    data->input[cmnd_count] = NULL;
    while (data->cmnds[++i])
    {
        printf("CMNDS :: %d\n", i);
        if (ft_strncmp(data->paths[i], "pathnfound", 11))
        {
            if (get_in(data, i))
            {
                free_str(data->input[i]);
                data->input[i] = get_in(data, i);
            }
            else
                data->input[i] = NULL;
            data->input[i] = exec_cmnd(data, i);
            printf("EXECCMND FINISHED!\n");
            printf("RETURN: %s\n", data->input[i]);
            // write(open_out(data, i), data->input[i], ft_strlen(data->input[i]));
        }
        printf("EXIT\n");
    }
}

