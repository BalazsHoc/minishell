/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_8.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:58:54 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/18 14:58:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int if_exec_cmnds_utils_4(t_pipex *data, int index, int i)
{
	if (data->l[index]->cmnd_count == 1)
		return (write(2, "bash: ", 6),
			write(2, data->l[index]->cmnds[i][
				first_invalid_in(data, index, i)],
			ft_strlen(data->l[index]->cmnds[i][
				first_invalid_in(data, index, i)])),
						write(2, ": No such file or directory\n", 29),
							exit_child(data, index, i, 1), 1);
	else
		return (write(2, "bash: ", 6),
			write(2, data->l[index]->cmnds[i][
				first_invalid_in(data, index, i)],
			ft_strlen(data->l[index]->cmnds[i][
				first_invalid_in(data, index, i)])),
						write(2, ": No such file or directory\n", 29),
							exit_child(data, index, i, 0), 1);
}

int	skip_nl(t_pipex *data)
{
	while (data->here_2_old < data->chars_in_line
		&& data->line[data->here_2_old]
		&& (data->line[data->here_2_old] == '\n'
			|| is_space(data->line[data->here_2_old])))
	{
		if (data->here_2 == data->here_2_old)
			data->here_2++;
		data->here_2_old++;
	}
	return (1);
}
