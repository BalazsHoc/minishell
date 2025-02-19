/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_is_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:47 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/11 15:18:48 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    print_that_shit(t_pipex *data, int index_1)
{
    int    i;
    int    j;

    // i = -1;
    printf("|\n");
    // while (data->cur_env[++i])
    //     printf("%s\n", data->cur_env[i]);
    i = -1;
    while (data->l[index_1]->cmnds[++i])
    {
        j = -1;
        while (data->l[index_1]->cmnds[i][++j])
        {
            if (data->l[index_1]->cmnds[i][j])
                printf("ELEM: %d:%d | |%s| ", i,
                    j, data->l[index_1]->cmnds[i][j]);
            if (data->l[index_1]->red_cmnd[i][j])
                printf("X\n");
            else
                printf("\n");
        }
        j = -1;
        if (data->l[index_1]->ops && data->l[index_1]->ops[i])
        {
            while (data->l[index_1]->ops[i][++j])
                printf("OP:   %d:%d | |%s|\n", i,
                    j, data->l[index_1]->ops[i][j]);
        }
        if (data->l[index_1]->input)
        printf("PATH: |%s|\n", data->l[index_1]->paths[i]);
    }
}

void	init_paths_2(t_pipex *data, int i)
{
	int	j;
	int	k;

	j = -1;
	while (data->l[i]->ops[++j])
	{
		k = -1;
		while (data->l[i]->ops[j][++k])
		{
			if (!access(data->l[i]->ops[j][k], X_OK)
				&& !one_of_those(data->l[i]->ops[j][k])
				&& (!ft_strncmp(data->l[i]->ops[j][0], "env", 4)
				|| !ft_strncmp(data->l[i]->ops[j][0], "/bin/env", 9)
				|| !ft_strncmp(data->l[i]->ops[j][0], "/usr/bin/env", 13))
				&& (!ft_strncmp(data->l[i]->ops[j][k], "../", 3)
					|| !ft_strncmp(data->l[i]->ops[j][k], "./", 2)))
			{
				free_str(&data->l[i]->paths[j]);
				data->l[i]->paths[j] = ft_strdup(data, data->l[i]->ops[j][k]);
				return ;
			}
			else
				errno = data->last_exit_status;
		}
	}
}

void	init_rest(t_pipex *data, int i)
{
	init_ops(data, i);
	init_paths(data, i, -1);
	init_paths_2(data, i);
	// print_that_shit(data, i);
	check_folder(data, i, -1, -1);
	start_exec(data, i, -1, 0);
}

int	set_err_old(t_pipex *data)
{
	data->last_exit_status = 2;
	data->here_2_old = count_nl(data, data->here_2_old);
	data->here_2 = data->here_2_old;
	return (1);
}
