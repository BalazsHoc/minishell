#include "minishell.h"


// // char    *create_tmp(t_pipex *data, int index, char *tmp_name, int count)
// // {
// //     char *cur_name;
// //     char *count_a;
// //     struct dirent* cur_file;
// //     DIR *cur_dir;

// //     (void)index;
// //     cur_dir = opendir(data->cur_path);
// //     count_a = ft_itoa(count);
// //     cur_name = ft_strjoin(tmp_name, count_a);
// //     if ((cur_dir = opendir(data->cur_path)) == NULL)
// //         return (printf("no such dir\n"), error_code(data, NULL, 0, 0), NULL);
// //     while ((cur_file = readdir(cur_dir)) != NULL)
// //     {
// //         printf("TEST FOR NOTHING INSIDE THE FOLDER!\n");
// //         if (!ft_strncmp(cur_file->d_name, cur_name, bigger_one(cur_file->d_name, cur_name)))
// //         {
// //             count++;
// //             count_a = ft_itoa(count);
// //             free(cur_name);
// //             cur_name = ft_strjoin(tmp_name, count_a);
// //             closedir(cur_dir);
// //             if ((cur_dir = opendir(data->cur_path)) == NULL)
// //                 return (printf("no such dir\n"), error_code(data, NULL, 0, 0), NULL);
// //         }
// //         if (count_a)
// //         {
// //             free(count_a);
// //             count_a = NULL;
// //         }
// //     }
// //     closedir(cur_dir);
// //     printf("CUR_FILE_NAME: %s\n", cur_name);
// //     return (cur_name);
// // }

void create_pipes(int (*pipes)[2], int cmnd_count)
{
    int i;

    i = -1;
    while (++i <= cmnd_count)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }
}

void close_pipes(int (*pipes)[2], int cmnd_count)
{
    int i;

    i = -1;
    while (++i <= cmnd_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}