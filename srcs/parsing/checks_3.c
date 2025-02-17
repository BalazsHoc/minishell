/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:11:30 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 15:11:31 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_folder_utils_4(t_pipex *data, int index, int i)
{
	write(2, "bash: ", 7);
	write(2, data->l[index]->ops[i][0], ft_strlen(data->l[index]->ops[i][0]));
	write(2, ": Permission denied\n", 21);
	exit_child(data, index, i, 126);
}

void	check_folder_utils_5(t_pipex *data, int index, int i)
{
	write(2, "bash: ", 7);
	write(2, data->l[index]->ops[i][0], ft_strlen(data->l[index]->ops[i][0]));
	write(2, ": No such file or directory\n", 29);
	exit_child(data, index, i, 127);
}

void	check_folder_utils_6(t_pipex *data, int index, int i)
{
	DIR	*ptr;

	ptr = NULL;
	ptr = opendir(data->l[index]->ops[i][0]);
	if (ptr)
		return (closedir(ptr),
			check_folder_utils_3(data, index, i));
	else if (one_of_those(data->l[index]->ops[i][0]))
		return (check_folder_utils_3(data, index, i));
	else if (errno == EACCES)
		return (check_folder_utils_4(data, index, i));
	else
		return (check_folder_utils_5(data, index, i));
}

void	check_folder(t_pipex *data, int index, int i, int j)
{
	while (data->l[index]->cmnds[++i])
	{
		j = -1;
		while (check_folder_utils_1(data, index, i) && i++ != INT_MIN)
		{
			if (!data->l[index]->cmnds[i])
				return ;
		}
		while (data->l[index]->ops[i][0][++j])
		{
			if (check_folder_utils_2(data, index, i, j))
				return (check_folder_utils_6(data, index, i));
		}
	}
}
