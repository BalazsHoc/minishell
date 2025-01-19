#include "minishell.h"


// char    *create_tmp(t_pipex *data, int index, char *tmp_name, int count)
// {
//     char *cur_name;
//     char *count_a;
//     struct dirent* cur_file;
//     DIR *cur_dir;

//     (void)index;
//     cur_dir = opendir(data->cur_path);
//     count_a = ft_itoa(count);
//     cur_name = ft_strjoin(tmp_name, count_a);
//     if ((cur_dir = opendir(data->cur_path)) == NULL)
//         return (printf("no such dir\n"), error_code(data), NULL);
//     while ((cur_file = readdir(cur_dir)) != NULL)
//     {
//         // printf("TEST FOR NOTHING INSIDE THE FOLDER!\n");
//         if (!ft_strncmp(cur_file->d_name, cur_name, bigger_one(cur_file->d_name, cur_name)))
//         {
//             count++;
//             count_a = ft_itoa(count);
//             free(cur_name);
//             cur_name = ft_strjoin(tmp_name, count_a);
//             closedir(cur_dir);
//             if ((cur_dir = opendir(data->cur_path)) == NULL)
//                 return (printf("no such dir\n"), error_code(data), NULL);
//         }
//         if (count_a)
//         {
//             free(count_a);
//             count_a = NULL;
//         }
//     }
//     closedir(cur_dir);
//     printf("CUR_FILE_NAME: %s\n", cur_name);
//     return (cur_name);
// }

void create_pipes(t_pipex *data, int index)
{
    int i;

    i = -1;
    while (++i < data->lines[index]->cmnd_count)
    {
        // printf("CREATING: %d | I:  %d\n", index, i);
        if (pipe(data->lines[index]->pipes[i]) == -1)
        {
            perror("pipe");
            error_code(data);
        }
    }
}

void create_buf_pipe(t_pipex *data, int index_1, int index_2)
{
    if (pipe(data->lines[index_1]->buf_pipes[index_2]) == -1)
    {
        perror("pipe");
        error_code(data);
    }
}

void close_everything(t_pipex *data, int index_1)
{
    int i;

    i = -1;
    while (++i < data->lines[index_1]->cmnd_count)
        close_pipes(data, index_1, i);
    close_pipes_array(data, index_1);
}

void close_children_pipes(t_pipex *data, int index_1, int index_2)
{
    close_pipes_array(data, index_1);
    close_pipes(data, index_1, index_2);
    close_pipe(data, &data->fd_out);
    close_pipe(data, &data->fd_in);
}

void close_pipes(t_pipex *data, int index_1, int index_2)
{
    close_pipe(data, &data->lines[index_1]->fd_infiles[index_2]);
    close_pipe(data, &data->lines[index_1]->fd_outfiles[index_2]);
    close_pipe(data, &data->lines[index_1]->buf_pipes[index_2][0]);
    close_pipe(data, &data->lines[index_1]->buf_pipes[index_2][1]);
}

void close_pipes_array(t_pipex *data, int index_1)
{
    int i;

    i = -1;
    while (++i < data->lines[index_1]->cmnd_count)
    {
        // printf("CLOSING: %d | I: %d\n", index_1, i );
        // if (data->lines[index]->pipes[i][0] > 2 && printf("CLOSING0: %d | I: %d\n", index, i) && close(data->lines[index]->pipes[i][0]) == -1)
        if (data->lines[index_1]->pipes[i][0] > 0)
            close_pipe(data, &data->lines[index_1]->pipes[i][0]);
        if (data->lines[index_1]->pipes[i][1] > 0)
            close_pipe(data, &data->lines[index_1]->pipes[i][1]);
        if (data->lines[index_1]->buf_pipes[i][0] > 0)
            close_pipe(data, &data->lines[index_1]->buf_pipes[i][0]);
        if (data->lines[index_1]->buf_pipes[i][1] > 0)
            close_pipe(data, &data->lines[index_1]->buf_pipes[i][1]);
    }
}

void close_buf_pipes(t_pipex *data, int index_1)
{
    int i;

    i = -1;
    while (++i < data->lines[index_1]->cmnd_count)
    {
        // printf("CLOSING: %d | I: %d\n", index_1, i );
        // if (data->lines[index]->pipes[i][0] > 2 && printf("CLOSING0: %d | I: %d\n", index, i) && close(data->lines[index]->pipes[i][0]) == -1)
        if (data->lines[index_1]->pipes[i][0] > 0)
            close_pipe(data, &data->lines[index_1]->pipes[i][0]);
        if (data->lines[index_1]->pipes[i][1] > 0)
            close_pipe(data, &data->lines[index_1]->pipes[i][1]);
        if (data->lines[index_1]->buf_pipes[i][0] > 0)
            close_pipe(data, &data->lines[index_1]->buf_pipes[i][0]);
        if (data->lines[index_1]->buf_pipes[i][1] > 0)
            close_pipe(data, &data->lines[index_1]->buf_pipes[i][1]);
    }
}

void close_pipe(t_pipex *data, int *fd)
{
    // if (*fd > 2 && printf("CLOSE: %d\n", *fd) && close(*fd) == -1)
    if (*fd > 2 && close(*fd) == -1)
    {
        perror("close");
        error_code(data);
    }
    *fd = -1;
}