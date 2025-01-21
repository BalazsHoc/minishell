#include "../../minishell.h"

void    check_folder(t_pipex *data, int index)
{
    int i;
    int j;
    DIR *ptr;

    i = -1;
    ptr = NULL;
    while (data->lines[index]->cmnds[++i])
    {
        j = -1;
        while (!data->lines[index]->ops[i][0] || ft_strncmp(data->lines[index]->paths[i], "pathnfound", 11))
        {
            i++;
            if (!data->lines[index]->cmnds[i])
                return ;
        }
        while (data->lines[index]->ops[i][0][++j]) 
        {
            if (data->lines[index]->ops[i][0][j] == '/')
            {
                ptr = opendir(data->lines[index]->ops[i][0]);
                if (ptr)
                    return (printf("bash: %s: Is a directory\n", data->lines[index]->ops[i][0]), closedir(ptr), exit_child(data, index, i, 126));
                else if (errno == EACCES)
                    return (printf("bash: %s: Permission denied\n", data->lines[index]->ops[i][0]), exit_child(data, index, i, 126)); 
                else if (errno == ENOTDIR)
                    return (printf("bash: %s: No such file or directory\n", data->lines[index]->ops[i][0]), exit_child(data, index, i, 127));
            }
        }
    }
}
