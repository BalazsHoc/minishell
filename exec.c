#include "minishell.h"

char *join_this(char *s1, char *s2)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!s2)
        return (free_str(&s1), NULL);
    while (s1 && s1[i])
        i++;
    while (s2 && s2[j])
        j++;
    if (i + j == 0)
        return (NULL);
    new = malloc(sizeof(char) * (i + j + 1));
    if (!new)
        return (free_str(&s1), NULL);
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
    free_str(&s1);
    return (new);
}

// void	handle_pwd_tmp(t_pipex *data, int index)
// {
// 	while (!is_valid_cwd(data))
// 		chdir("..");
// 	data->tmp = create_tmp(data, index, "tmp_", 0);
// }

// void    handle_child(t_pipex *data, int index_1, int index_2, int fd)
// {
//     if (is_in_inline(data, index_1, index_2) != -1
//         && !ft_strncmp(data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2)], "<", 2)) // if its simple infile
//     {
//         fd = open(data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2) + 1], O_RDONLY);
//         if (fd == -1)
//             return (printf("error open\n"), error_code(data));
//     }
//     // if (data->lines[index_1]->pipes[index_2][0])
//     //     printf("OPEN\n");
//     // else
//     //     printf("CLOSED 1\n");
//     // if (dup2(data->lines[index_1]->pipes[0][0], STDIN_FILENO) == -1)
//     //     perror("dup2 open 0");
//     // if (data->lines[index_1]->cmnd_count > 1 && dup2(data->lines[index_1]->pipes[0][1], STDOUT_FILENO) == -1)
//     //     perror("dup2 open 0");
//     // if (data->lines[index_1]->cmnd_count == 1 && dup2(data->lines[index_1]->pipes[0][1], STDOUT_FILENO) == -1)
//     //     perror("dup2 open 0");
//     // printf("CMND: %s\n", data->lines[index_1]->ops[index_2][0]);
//     if (!fd && (!data->input && index_2 > 0) && dup2(data->lines[index_1]->pipes[index_2 + 1][0], STDIN_FILENO) == -1)  // 0 | echo hi X | cat << EOF | head
//         return (printf("error dup this one\n"), error_code(data));                                      // echo liest von sich selber
//     else if (!fd && (data->input && index_2 > 0) && dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO) == -1) // 0 | echo hi X | cat << EOF X | head
//         return (perror("error dup2 this"), error_code(data));                                               // cat liest von davor
//     else if (fd && dup2(fd, STDIN_FILENO) == -1)
//         return (printf("error dup2\n"), error_code(data));
//     if (!data->fd_out && index_2 < data->lines[index_1]->cmnd_count - 1 && // 0 | echo hi | cat << EOF | head X // normal / cat schreibt next 
//         !(is_red_inline(data, index_1, index_2 + 1) != -1 && !ft_strncmp(data->lines[index_1]->cmnds[index_2 + 2][is_red_inline(data, index_1, index_2 + 1)], "<<", 3))
//         && dup2(data->lines[index_1]->pipes[index_2 + 2][1], STDOUT_FILENO) == -1)
//         return (printf("dup2"), error_code(data));
//     if (!data->fd_out && index_2 < data->lines[index_1]->cmnd_count - 1 && //  0  |  echo hi    X |  cat << EOF  | head // echo schreibt in sich selbst
//         &&  dup2(data->lines[index_1]->pipes[index_2 + 1][1], STDOUT_FILENO) == -1)
//         return (printf("dup2"), error_code(data));
//     else if (data->fd_out && dup2(data->fd_out, STDOUT_FILENO) == -1)
//         return (printf("dup2"), error_code(data));
//     if (fd)
//         close(fd);
//     close_pipes(data, index_1);
//     if (!(data->lines[index_1]->cmnds[index_2 + 1] && is_red_inline(data, index_1, index_2 + 1) != -1
//         && ft_strncmp(data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2 + 1)], "<<", 3)))
//     {
//         if (execve(data->lines[index_1]->paths[index_2], data->lines[index_1]->ops[index_2], NULL) == -1)
//             printf("EXECVE FAILED!!!\n"); // handle if execve fails!
//         perror("execve"), error_code(data);
//     }
// }

int open_this_read(t_pipex *data, char *str)
{
    int fd;

    // str = ft_strtrim(str, ".");
    printf("OPEN: STR: %s\n", str);
    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        error_code(data);
    }   
    return (fd);
}

int open_this_write(t_pipex *data, char *str)
{
    int fd;

    // str = ft_strtrim(str, ".");
    // printf("OPEN: STR: %s\n", str);
    fd = open(str, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        error_code(data);
    }   
    return (fd);
}

int check_here_doc(t_pipex *data, int index_1, int index_2)
{
    if ((is_red_inline(data, index_1, index_2) != -1 && !data->lines[index_1]->red_cmnd[index_2][is_red_inline(data, index_1, index_2)]
        && !ft_strncmp(data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2)], "<<", 3)))
        // return (printf("HEREDOC!\n"), 1);
        return (1);
    return (0);
    // return (prin1tf("NO HEREDOC\n"), 0);
}

int check_infile(t_pipex *data, int index_1, int index_2)
{
    if (is_in_inline(data, index_1, index_2) != -1 && !data->lines[index_1]->red_cmnd[index_2][is_red_inline(data, index_1, index_2)]
        && !ft_strncmp(data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2)], "<", 2))
        return (1);
    return (0);
}

void    handle_child(t_pipex *data, int index_1, int index_2, int fd)
{
    int dev_null;

    // printf("CHILD: I: %d | cmnd_count: %d\n", index_2, data->lines[index_1]->cmnd_count);
    dev_null = open_this_write(data, "/dev/null");
    if (check_infile(data, index_1, index_2))
        fd = open_this_read(data, data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2) + 1]);
    if (!fd && data->input && dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO) == -1)
        return (perror("error dup2"), error_code(data));
    else if (!fd && !data->input && index_2 > 0 && dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO) == -1)
        return (perror("error dup2"), error_code(data));
    else if (fd && dup2(fd, STDIN_FILENO) == -1)
        return (perror("error dup2"), error_code(data));
    // close_pipe(data, &data->lines[index_1]->pipes[index_2][0]);
    if (!data->fd_out && index_2 < data->lines[index_1]->cmnd_count - 1
        && !check_here_doc(data, index_1, index_2 + 1) && dup2(data->lines[index_1]->pipes[index_2 + 1][1], STDOUT_FILENO) == -1)
        return (perror("dup2"), error_code(data));
    else if (!data->fd_out && index_2 < data->lines[index_1]->cmnd_count - 1 && check_here_doc(data, index_1, index_2 + 1) && dup2(dev_null, STDOUT_FILENO) == -1)
                return (printf("dup2"), error_code(data));
    else if (data->fd_out && dup2(data->fd_out, STDOUT_FILENO) == -1)
        return (perror("dup2"), error_code(data));
    // close_pipe(data, &data->lines[index_1]->pipes[index_2][1]);
    close_pipe(data, &fd);
    close_pipe(data, &dev_null);
    close_pipes(data, index_1);
    if (execve(data->lines[index_1]->paths[index_2], data->lines[index_1]->ops[index_2], NULL) == -1)
        perror("execve"), error_code(data);
}

void    handle_mini_child(t_pipex *data, int index_1, int index_2, int fd)
{
    int dev_null;
    // printf("MINICHILD: I: %d | cmnd_count: %d\n", index_2, data->lines[index_1]->cmnd_count);
    dev_null = open_this_write(data, "/dev/null");
    data->buf_int = 0;
    if (check_infile(data, index_1, index_2))
        fd = open_this_read(data, data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2) + 1]);
    if (!fd && data->input && dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO) == -1)
        return (perror("error dup2"), error_code(data));
    else if (!fd && !data->input && index_2 > 0 && dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO) == -1)
        return (perror("error dup2"), error_code(data));
    else if (fd && dup2(fd, STDIN_FILENO) == -1)
        return (perror("error dup2"), error_code(data));
    if (data->buf_int == -1)
        return (perror("dup() failed"), error_code(data));
    if (!data->fd_out && index_2 < data->lines[index_1]->cmnd_count - 1
        && !check_here_doc(data, index_1, index_2 + 1))
        data->buf_int = dup2(data->lines[index_1]->pipes[index_2 + 1][1], STDOUT_FILENO);
    else if (!data->fd_out && index_2 < data->lines[index_1]->cmnd_count - 1 && check_here_doc(data, index_1, index_2 + 1))
        data->buf_int = dup2(dev_null, STDOUT_FILENO);
    else if (data->fd_out)
        data->buf_int = dup2(data->fd_out, STDOUT_FILENO);
    if (data->buf_int == -1)
        return (perror("dup2"), error_code(data));
    close_pipe(data, &fd);
    close_pipe(data, &dev_null);
    close_pipes(data, index_1);
    mini_child(data, index_1, index_2);
    if (dup2(data->buf_int, STDOUT_FILENO) == -1)
        return (perror("dup2"), error_code(data));
    close_pipe(data, &data->buf_int);
    error_code(data);
}

void exec_cmnd(t_pipex *data, int index_1, int index_2)
{
	signal_change(2);
    data->pid[index_2] = fork();
	if (data->pid[index_2] < 0)
        return (perror("fork"), error_code(data));
	else if (!data->pid[index_2])
        handle_child(data, index_1, index_2, 0);
    else if (data->pid[index_2] && data->input)
    {
        write(data->lines[index_1]->pipes[index_2][1], data->input, ft_strlen(data->input));
        // write(data->lines[index_1]->pipes[index_2][1], "\n", 2);
        free(data->input);
        data->input = NULL;
    }
}

void exec_mini(t_pipex *data, int index_1, int index_2)
{
    if (data->lines[index_1]->cmnds[1])
    {
        data->pid[index_2] = fork();
        if (data->pid[index_2] < 0)
            return (perror("fork"), error_code(data));
        else if (!data->pid[index_2])
            handle_mini_child(data, index_1, index_2, 0);
    }
    else
        mini_parent(data, index_1, index_2);
}
