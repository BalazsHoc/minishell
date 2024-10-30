#include "minishell.h"

int free_this(char *s)
{
    if (s)
        free(s);
    return (1);
}

int change_dir(t_pipex *data, int *index)
{
    // to keep it running:
    (void)data;
    (void)index;
    return (1);
    // if (cd)
    //     *index++;
    // return (1); // every return
}

int is_red_inline(t_pipex *data, int index)
{
    int i;
    int check;

    i = -1;
    check = -1;
    while (data->cmnds[index] && data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2)
            || !ft_strncmp(data->cmnds[index][i], "<<", 3))
            check = i;
    }
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
        if (data->cmnds[index][i][0] == '<' && !data->cmnds[index][i][1])
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

char *get_input(char *file_EOF, t_pipex *data, int index_1, int index_2)
{
    int fd;
    char *buf;
    char *key;

    printf("THIS: %s\n", data->cmnds[index_1][index_2]);
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<", 2))
    {
        printf("PENIS\n");
        fd = open(file_EOF, O_RDONLY);   
        if (fd == -1)
            return (printf("bash: %s: no such file or directory\n", file_EOF), NULL);
    }
    else
        fd = 0;
    printf("FD: %d\n", fd);
    buf = get_next_line(fd, 0);
    key = data->cmnds[index_1][index_2 + 1];
    printf("KEY: %s", key);
    file_EOF = NULL;
    while (buf && !ft_strcmp_2(buf, key))
    {
        file_EOF = join_this(file_EOF, buf);
        free(buf);
        buf = get_next_line(fd, 0);
        printf("THIS: %s$\n", buf);
    }
    if (fd > 2)
        close(fd);
    return (file_EOF);
}

// char *get_input_user(data->cmnds[index][i + 1])
// {
//     int i;
// }

char *get_in(t_pipex *data, int index)
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
        if (!ft_strncmp(data->cmnds[index][i], "<<", 3) && i != is_red_inline(data, index))
        {
            infile = get_input(data->cmnds[index][i + 1], data, index, i);
            free_str(infile);
        }
    }
    if (!infile)
        return (NULL);
    fd = open(infile, O_RDONLY);
    if (fd == -1)
        return (NULL);
    return (close(fd), infile);
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

void start_exec(t_pipex *data, char **env)
{
    int     i;
    int     fd;
    
    i = -1;
    data->input = NULL;
    while (data->cmnds[++i] && change_dir(data, &i))
    {
        fd = open_out(data, i);
        if (ft_strncmp(data->paths[i], "pathnfound", 11)
            && (is_valid_in(data, i) || is_red_inline(data, i) != -1
            || (!is_valid_in(data, i) && is_in_inline(data, i) == -1)))
        {
            if ((is_valid_in(data, i) || (!is_valid_in(data, i) && is_red_inline(data, i) != -1)) && free_this(data->input))
                data->input = get_input(get_in(data, i), data, i, is_red_inline(data, i));
            printf("INPUT: %s$\n", data->input);
            data->input = exec_cmnd(data, i, env);
            printf("EXECCMND FINISHED!\n");
            printf("_________________________________________________________________________________________\n");
            if (fd != -2)
                write(open_out(data, i), data->input, ft_strlen(data->input));
            else if (!data->cmnds[i + 1])
                write(1, data->input, ft_strlen(data->input));
            printf("_________________________________________________________________________________________\n");
        }
        else if (ft_strncmp(data->paths[i], "pathnfound", 11) 
            && (is_valid_in(data, i) || (!is_valid_in(data, i)
            && is_red_inline(data, i) != -1)))
            printf("BASH: %s: no such file or directory\n", data->cmnds[i][is_red_inline(data, i) + 1]);
        close(fd);
        printf("EXIT\n");
    }
}

// void start_exec(t_pipex *data)
// {
//     int     i;
//     int     fd;
    
//     i = -1;
//     data->input = NULL;
//     while (data->cmnds[++i])
//     {
//         fd = open_out(data, i);
//         if (ft_strncmp(data->paths[i], "pathnfound", 11)
//             && (get_in(data, i) || (!get_in(data, i)
//             && is_red_inline(data, i) == -1)))
//         {
//             free_str(data->input);
//             data->input = NULL;
//             data->input = exec_cmnd(data, i);
//         }
//         else if (ft_strncmp(data->paths[i], "pathnfound", 11) && is_in_inline(data, i))
//         {
//             free_str(data->input);
//             data->input = 
//         }
//             if (fd != -2)
//                 write(open_out(data, i), data->input, ft_strlen(data->input));
//             else if (!data->cmnds[i + 1])
//                 write(1, data->input, ft_strlen(data->input));
//         else if (ft_strncmp(data->paths[i], "pathnfound", 11) 
//             && (get_in(data, i) || (!get_in(data, i)
//             && is_red_inline(data, i) != -1)))
//             printf("bash: %s: no such file or directory\n", data->cmnds[i][is_red_inline(data, i) + 1]);
//         close(fd);
//         printf("EXIT\n");
//     }
// }


// 1. infile && !input

// 2. !infile && !input

// 3. infile && input

// 4. !infile && input



// TODO 

// echo hi | wc --> 3 chars
// vs.
// echo "hi" | wc --> 3 not 5 chars

