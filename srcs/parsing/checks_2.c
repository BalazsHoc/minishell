/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:50:09 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:50:11 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_open(t_pipex *data, char *line)
{
	int	open;
	int	i;

	i = data->here_2_old -1;
	open = 0;
	while (line[++i])
	{
		if (is_quote_one(line[i]) && !open)
			open = 1;
		else if (is_q_2(line[i]) && !open)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1)
				|| (is_q_2(line[i]) && open == 2)))
			open = 0;
	}
	return (open);
}

int	syntax_check(t_pipex *data, int i, int count)
{
	int	word;
	int	open;

	word = 0;
	open = 0;
	if (i == 0 || (data->line[i] != '\n'))
		i--;
	while (data->line[++i] && data->line[i] != '\n')
	{
		handle_open(data, i, &open);
		if (!open && (i == data->here_2_old
				|| !data->line[i + 1]) && data->line[i] == '|')
			return (0);
		else if (!open && !is_real_pipe(data->line, i)
			&& !is_space(data->line[i]) && ++word)
			count = 0;
		else if (!open && is_real_pipe(data->line, i))
			count++;
		if (count >= 2)
			return (0);
	}
	return (1);
}

int	check_folder_utils_1(t_pipex *data, int index, int i)
{
	if (!data->l[index]->ops[i][0]
			|| ft_strncmp(data->l[index]->paths[i], "pathnfound", 11)
				|| data->l[index]->exit_codes[i])
		return (1);
	return (0);
}

int	check_folder_utils_2(t_pipex *data, int index, int i, int j)
{
	if ((data->l[index]->ops[i][0][j] == '/'
			|| one_of_those(data->l[index]->ops[i][0]))
				&& (!check_cmnd_as_dir(data, index, i)))
		return (1);
	return (0);
}

void	check_folder_utils_3(t_pipex *data, int index, int i)
{
	printf("bash: %s: Is a directory\n", data->l[index]->ops[i][0]);
	exit_child(data, index, i, 126);
}
