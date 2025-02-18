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
