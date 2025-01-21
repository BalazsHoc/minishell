#include "minishell.h"

char *join_this(char *s1, char *s2, t_pipex *data)
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
    new = ft_calloc(sizeof(char), (i + j + 1 + 1), data);
    new[i + j] = '\n';
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
    // printf("OPEN: STR: %s\n", str);
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
    // return (printf("NO HEREDOC\n"), 0);
}

int check_infile(t_pipex *data, int index_1, int index_2)
{
    if (is_in_inline(data, index_1, index_2) != -1 && !data->lines[index_1]->red_cmnd[index_2][is_red_inline(data, index_1, index_2)]
        && !ft_strncmp(data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2)], "<", 2))
        return (1);
    return (0);
}

void    handle_child(t_pipex *data, int index_1, int index_2)
{
    // printf("CHILD: I: %d | cmnd_count: %d | FD: %d \n", index_2, data->lines[index_1]->cmnd_count, data->lines[index_1]->fd_outfiles[index_2]);
    data->fd_in = 0;
    data->fd_out= 0;
    if (check_infile(data, index_1, index_2))
        data->lines[index_1]->fd_infiles[index_2] = open_this_read(data, data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2) + 1]);
    if (data->lines[index_1]->fd_infiles[index_2] != -1)
        data->fd_in = dup2(data->lines[index_1]->fd_infiles[index_2], STDIN_FILENO);
    // IF NORMAL
    else if (index_2 > 0 && data->lines[index_1]->pipes[index_2][1] != -1 && data->lines[index_1]->fd_infiles[index_2] == -1
        && !check_here_doc(data, index_1, index_2))
        data->fd_in = dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO);
    // IF HEREDOC
    else if (data->lines[index_1]->buf_pipes[index_2][1] != -1 && data->lines[index_1]->fd_infiles[index_2] == -1 
        && check_here_doc(data, index_1, index_2))
        data->fd_in = dup2(data->lines[index_1]->buf_pipes[index_2][0], STDIN_FILENO);
    if (data->fd_in == -1)
        return (perror("in dup2"), close_children_pipes(data, index_1, index_2), error_code(data));
    if (index_2 < data->lines[index_1]->cmnd_count - 1
        && data->lines[index_1]->pipes[index_2 + 1][1] != -1
        && data->lines[index_1]->fd_outfiles[index_2] == -1)
        data->fd_out = dup2(data->lines[index_1]->pipes[index_2 + 1][1], STDOUT_FILENO);
    else if (data->lines[index_1]->fd_outfiles[index_2] != -1)
        data->fd_out = dup2(data->lines[index_1]->fd_outfiles[index_2], STDOUT_FILENO);
    if (data->fd_out == -1)
        return (perror("out dup2"), close_children_pipes(data, index_1, index_2), error_code(data));
    close_children_pipes(data, index_1, index_2);
    if (execve(data->lines[index_1]->paths[index_2], data->lines[index_1]->ops[index_2], NULL) == -1)
        perror("execve"), error_code(data);
}

void    handle_mini_child(t_pipex *data, int index_1, int index_2)
{
    data->fd_in = 0;
    data->fd_out= 0;
    if (check_infile(data, index_1, index_2))
        data->lines[index_1]->fd_infiles[index_2] = open_this_read(data, data->lines[index_1]->cmnds[index_2][is_red_inline(data, index_1, index_2) + 1]);
    if (data->lines[index_1]->fd_infiles[index_2] != -1)
        data->fd_in = dup2(data->lines[index_1]->fd_infiles[index_2], STDIN_FILENO);
    else if (data->lines[index_1]->pipes[index_2][1] != -1 && data->lines[index_1]->fd_infiles[index_2] == -1
        && !check_here_doc(data, index_1, index_2) && index_2 > 0)
        data->fd_in = dup2(data->lines[index_1]->pipes[index_2][0], STDIN_FILENO);
    else if (data->lines[index_1]->buf_pipes[index_2][1] != -1 && data->lines[index_1]->fd_infiles[index_2] == -1
        && check_here_doc(data, index_1, index_2))
        data->fd_in = dup2(data->lines[index_1]->buf_pipes[index_2][0], STDIN_FILENO);
    if (data->fd_in == -1)
        return (perror("error dup2"), error_code(data));
    if (index_2 < data->lines[index_1]->cmnd_count - 1
        && data->lines[index_1]->fd_outfiles[index_2] == -1
        && data->lines[index_1]->pipes[index_2 + 1][1] != -1)
        data->fd_out = dup2(data->lines[index_1]->pipes[index_2 + 1][1], STDOUT_FILENO);
    else if (data->lines[index_1]->fd_outfiles[index_2] != -1)
        data->fd_out = dup2(data->lines[index_1]->fd_outfiles[index_2], STDOUT_FILENO);
    if (data->fd_out == -1)
        return (perror("error dup2"), error_code(data));
    mini_child(data, index_1, index_2);
    close_pipe(data, &data->fd_out);
    close_children_pipes(data, index_1, index_2);
    error_code(data);
}

void exec_cmnd(t_pipex *data, int index_1, int index_2)
{
    signal_change(2);
    if (check_here_doc(data, index_1, index_2) && data->lines[index_1]->pipes[index_2][1])
        create_buf_pipe(data, index_1, index_2);
    data->pid[index_2] = fork();
	if (data->pid[index_2] < 0)
        return (perror("fork"), error_code(data));
	else if (!data->pid[index_2])
        handle_child(data, index_1, index_2);
    else if (data->pid[index_2] && data->lines[index_1]->input[index_2] && data->lines[index_1]->pipes[index_2][1])
    {
        write(data->lines[index_1]->buf_pipes[index_2][1], data->lines[index_1]->input[index_2], ft_strlen(data->lines[index_1]->input[index_2]));
        free_str(&data->lines[index_1]->input[index_2]);
    }
    close_pipe(data, &data->lines[index_1]->pipes[index_2][1]);
    
    // close_pipe(data, &data->lines[index_1]->buf_pipes[index_2][0]);
}

void exec_mini(t_pipex *data, int index_1, int index_2)
{
    if (data->lines[index_1]->cmnds[1])
    {
        if (check_here_doc(data, index_1, index_2) && data->lines[index_1]->pipes[index_2][1])
            create_buf_pipe(data, index_1, index_2);
        data->pid[index_2] = fork();
        if (data->pid[index_2] < 0)
            return (perror("fork"), error_code(data));
        else if (!data->pid[index_2])
            handle_mini_child(data, index_1, index_2);
    }
    else
        mini_parent(data, index_1, index_2);
}
