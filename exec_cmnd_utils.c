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

void close_pipes(t_pipex *data, int index)
{
    int i;

    i = -1;
    while (++i < data->lines[index]->cmnd_count)
    {
        // printf("CLOSING: %d | I: %d\n", index, i);
        // if (data->lines[index]->pipes[i][0] > 2 && printf("CLOSING0: %d | I: %d\n", index, i) && close(data->lines[index]->pipes[i][0]) == -1)
        if (data->lines[index]->pipes[i][0] > 2 && close(data->lines[index]->pipes[i][0]) == -1)
        {
            perror("close1");
            error_code(data);
        }
        else
            data->lines[index]->pipes[i][0] = -1;
        // if (data->lines[index]->pipes[i][1] > 2 && printf("CLOSING1: %d | I: %d\n", index, i) && close(data->lines[index]->pipes[i][1]) == -1)
        if (data->lines[index]->pipes[i][1] >= 0 && close(data->lines[index]->pipes[i][1]) == -1)
        {
            perror("close2");
            error_code(data);
        }
        else
            data->lines[index]->pipes[i][1] = -1;
    }
}

void close_pipe(t_pipex *data, int fd)
{
    // printf("CLOSE: %d\n", fd);
    if (fd > 2 && close(fd) == -1)
    {
        perror("close");
        error_code(data);
    }
}

void close_pipes_2(t_pipex *data, int index_1, int index_2)
{
    int i;

    i = -1;
    while (++i < data->lines[index_1]->cmnd_count)
    {
        // printf("CLOSING: %d | I: %d\n", index, i);
        if (i != index_2)
        {
            if (data->lines[index_1]->pipes[i][0] >= 0 && close(data->lines[index_1]->pipes[i][0]) == -1)
            {
                perror("close01");
                error_code(data);
            }
            if (data->lines[index_1]->pipes[i][1] >= 0 && close(data->lines[index_1]->pipes[i][1]) == -1)
            {
                perror("close02");
                error_code(data);
            }
        }
    }
}