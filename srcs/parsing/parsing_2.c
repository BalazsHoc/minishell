#include "../../minishell.h"

int is_red(t_pipex *data, int index_1, int index_2)
{
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<<", 3)
        || !ft_strncmp(data->cmnds[index_1][index_2], ">", 2)
        || !ft_strncmp(data->cmnds[index_1][index_2], "<", 2)
        || !ft_strncmp(data->cmnds[index_1][index_2], ">>", 3))
        return (1);
    return (0);
}

int check_reds(t_pipex *data)
{
    int i;
    int j;

    i = -1;
    while (data->cmnds[++i])
    {
        j = -1;
        while (data->cmnds[i][++j])
        {
            if (is_red(data, i, j) && !data->cmnds[i][j + 1])
            {
                if (!data->cmnds[i + 1])
                    return (printf("bash: syntax error near unexpected token `newline' \n"), exit_child(2, NULL, data), 0);
                return (printf("bash: syntax error near unexpected token `|'\n"), exit_child(2, NULL, data), 0);
            }
            else if (is_red(data, i, j) && is_red(data, i, j + 1))
                    return (printf("bash: syntax error near unexpected token `%s' \n", data->cmnds[i][j + 1]), exit_child(2, NULL, data), 0);
        }
    }
    return (1);
}

int count_reds(t_pipex *data, int index)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while (data->cmnds[index][++i])
    {
        if (is_red(data, index, i))
            count++;
    }
    return (count);
}

void ft_strcpy(char *s1, char *s2)
{
    int i;

    i = -1;
    while (s1[++i])
        s2[i] = s1[i];
}

void    fill_ops(t_pipex *data, int index)
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (data->cmnds[index][++i])
    {

        while (data->cmnds[index][i] && is_red(data, index, i))
            i += 2;
        if (data->cmnds[index][i])
        {
            // printf("I: %d S: %s\n", i, data->cmnds[index][i]);
            data->ops[index][++j] = ft_calloc(sizeof(char *), (count_chars(data->cmnds[index][i]) + 1));
            if (!data->ops[index][j])
                return (printf("malloc fail!\n"), error_code(data, NULL, 1, errno));
            data->ops[index][j][count_chars(data->cmnds[index][i])] = 0;
            ft_strcpy(data->cmnds[index][i], data->ops[index][j]);
        }
        else 
            break ;
    }
}

// char ***init_reds(t_pipex *data, char *line, int cmnd_count)
// {
//     int i;

//     i = -1;
//     check_reds(data, NULL, cmnd_count);
//     data->reds = malloc(sizeof(char **) * (cmnd_count + 1));
//     if (!data->reds)
//         return (perror("malloc fail!\n"), error_code(data, line, 1), NULL);
//     data->reds[cmnd_count] = 0;
//     while (++i < cmnd_count)
//     {
//         data->reds[i] = malloc(sizeof(char *) * (count_reds(data, line, i) + 1));
//         if (!data->reds[i])
//             return (perror("malloc fail!\n"), error_code(data, line, 1), NULL);
        

//     }
// }


// int search_for_it(t_pipex *data, int index)
// {
//     int i;

//     i = -1;
//     while (data->cmnds[index][++i])
//     {
//             if (!data->cmnds[index][i + 1])
//             {
//                 if (!data->cmnds[index + 1])
//                     return (printf("bash: syntax error near unexpected token `newline' \n"),
//                         exit_child(258, NULL, data), -1);
//                 return (printf("bash: syntax error near unexpected token `|'\n"),
//                     exit_child(258, NULL, data), -1);
//             }
//             return (1);
//         }
//         // if (ft_strncmp(data->cmnds[index][i], "<", 2))
//         // {
//         //     if (i > 0)
//         //         return (1);
//         //     else
//         //         return (printf("bash: %s: No such file or directory\n", data->cmnds[index][i]),
//         //             exit_child(1, NULL, data), -1);
//         // }
//     }
//     return (0);
// }

int count_ops(t_pipex *data, int index)
{
    int i;

    i = 0;
    while (data->cmnds[index][i])
        i++;
    return (i - (count_reds(data, index) * 2));
}

void parsing_2(t_pipex *data, int cmnd_count)
{
    int i;

    i = -1;
    data->ops = malloc(sizeof(char **) * (cmnd_count + 1));
    if (!data->ops)
        return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno));
    data->ops[cmnd_count] = 0;
    // data->reds = malloc(sizeof(char *) * (cmnd_count + 1));
    // if (!data->reds)
    //     return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno);
    // data->reds[cmnd_count] = 0;

    while (data->cmnds[++i])
    {
        data->ops[i] = malloc(sizeof(char *) * (count_ops(data, i) + 1));
        if (!data->ops[i])
            return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno));
        data->ops[i][count_ops(data, i)] = 0;
        fill_ops(data, i);
        // data->reds[i] = malloc(sizeof(char *) * (count_reds(data, i) + 1));
        // if (!data->reds[i])
        //     return (perror("malloc fail!\n"), error_code(data, NULL, 1));
        // data->reds[i] = fill_reds(data, i);
        // if (!data->reds[i])
        //     return ;
    }
}


