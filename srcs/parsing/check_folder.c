#include "../../minishell.h"

void    check_folder(t_pipex *data)
{
    int i;
    int j;

    i = -1;
    while (data->cmnds[++i])
    {
        j = -1;
        while (!data->ops[i][0] || ft_strncmp(data->paths[i], "pathnfound", 12))
        {
            i++;
            if (!data->cmnds[i])
                return ;
        }
        while (data->ops[i][0][++j]) 
        {
            if (data->ops[i][0][j] == '/')
            {
                if (opendir(data->ops[i][0]))
                    return (printf("bash: %s: Is a directory\n", data->ops[i][0]), exit_child(data, i, 126));
                else if (errno == 20)
                    return (printf("bash: %s: Permission denied\n", data->ops[i][0]), exit_child(data, i, 126)); 
                else
                    return (printf("bash: %s: No such file or directory\n", data->ops[i][0]), exit_child(data, i, 127));
            }
        }
    }
}