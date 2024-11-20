#include "../../minishell.h"

int count_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

void ft_strcpy(char *s1, char *s2)
{
    int i;

    i = -1;
    while (s1[++i])
        s2[i] = s1[i];
}

int count_reds(t_pipex *data, int index)
{
    int i;
    int count;

    i = -1;
    count = 0;
    // printf("COUNT REDS\n");
    while (data->cmnds[index][++i])
    {
        // printf("THIS %s\n", data->cmnds[index][i]);
        if (is_red(data, index, i))
            count++;
        if (!data->cmnds[index][i + 1])
            break;
    }
    // printf("COUNT REDS END\n");
    return (count);
}

int count_ops(t_pipex *data, int index)
{
    int i;

    i = 0;
    // printf("COUNT OPS\n");
    while (data->cmnds[index][i])
        i++;
    // printf("COUNT OPS END\n");
    return (i - (count_reds(data, index) * 2));
}

void    fill_ops(t_pipex *data, int index)
{
    int i;
    int j;

    i = -1;
    j = -1;

    // printf("FILL OPS\n");
    while (data->cmnds[index][++i])
    {
        while (data->cmnds[index][i] && is_red(data, index, i))
            i += 2;
        if (data->cmnds[index][i])
        {
            // printf("I: %d S: %s\n", i, data->cmnds[index][i]);
            // printf("COUNT op: %ld \n", ft_strlen(data->cmnds[index][i]));
            data->ops[index][++j] = ft_calloc(sizeof(char *), (ft_strlen(data->cmnds[index][i]) + 1));
            if (!data->ops[index][j])
                return (printf("malloc fail!\n"), error_code(data, NULL, 1, errno));
            data->ops[index][j][ft_strlen(data->cmnds[index][i])] = 0;
            ft_strcpy(data->cmnds[index][i], data->ops[index][j]);
        }
        else 
            break ;
    }
}