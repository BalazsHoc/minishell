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

int count_reds(t_pipex *data, int index_1, int index_2)
{
    int i;
    int count;

    i = -1;
    count = 0;
    // printf("COUNT REDS START\n");
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        // printf("THIS %s\n", data->cmnds[index][i]);
        if (is_red(data, index_1, index_2, i))
            count++;
        if (!data->lines[index_1]->cmnds[index_2][i + 1])
            break;
    }
    // printf("COUNT REDS END %d\n", count);
    return (count);
}

int count_ops(t_pipex *data, int index_1, int index_2)
{
    int i;
    int count;

    i = 0;
    count = 0;
    // printf("COUNT OPS START\n");
    while (data->lines[index_1]->cmnds[index_2][i])
    {
        // if (!data->lines[index_1]->red_cmnd[index_2][i])
        count++;
        i++;
    }
    // printf("COUNT OPS %d\n", count - (count_reds(data, index_1, index_2) * 2));
    return (count - (count_reds(data, index_1, index_2) * 2));
}

// void    fill_echo_exit(t_pipex *data, int index)
// {
//     data->ops[index][0] = ft_strdup("/bin/bash");
//     if (!data->ops[index][0])
//         error_code(data);
//     data->ops[index][1] = ft_strdup("-c");
//     if (!data->ops[index][1])
//         error_code(data);
//     data->ops[index][2] = ft_strdup("echo $?");
//     if (!data->ops[index][2])
//         error_code(data);
// }

void    fill_ops(t_pipex *data, int index_1, int index_2)
{
    int i;
    int j;

    i = -1;
    j = -1;

    // printf("FILL OPS\n");
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        while (data->lines[index_1]->cmnds[index_2][i] && is_red(data, index_1, index_2, i))
        {
            i += 2;
            if (!data->lines[index_1]->cmnds[index_2][i])
                break;
        }
        // if (data->lines[index_1]->cmnds[index_2][i] && !data->lines[index_1]->red_cmnd[index_2][i])
        if (data->lines[index_1]->cmnds[index_2][i])
        {
            // printf("I: %d S: %s\n", i, data->cmnds[index][i]);
            data->lines[index_1]->ops[index_2][++j] = ft_calloc(sizeof(char *), (ft_strlen(data->lines[index_1]->cmnds[index_2][i]) + 1), data);
            ft_strcpy(data->lines[index_1]->cmnds[index_2][i], data->lines[index_1]->ops[index_2][j]);
            // if (j == 0)
                // data->ops[index][0] = ft_strtrim(data->ops[index][j], " ");
        }
        else 
            break ;
    }
}
