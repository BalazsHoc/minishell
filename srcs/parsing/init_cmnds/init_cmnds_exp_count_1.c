/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_exp_count_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:54:54 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:54:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_pid(t_pipex *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork() failed!"), er_c(data), NULL);
	if (pid == 0)
		return (data->buf_str = NULL, er_c(data), exit(EXIT_SUCCESS), NULL);
	if (wait(NULL) == -1)
		return (perror("wait() failed!"), er_c(data), NULL);
	return (ft_itoa(pid, data));
}

int	c_e_0(t_pipex *data, int i, int open)
{
	if (open != 1 && data->line[i] == '$' && data->line[i + 1]
		&& data->line[i + 1] == '$')
		return (1);
	else if (open != 1 && data->line[i] == '$'
		&& data->line[i + 1] == '?')
		return (1);
	return (0);
}

void	c_e_1(t_pipex *data, char **elem, int *i, int open)
{
	if (open != 1 && data->line[*i] == '$' && data->line[*i + 1] == '?')
		*elem = ft_itoa(data->last_exit_status, data);
	else
		*elem = get_pid(data);
	*i += 2;
}

int	c_e_2(t_pipex *data, int i, int open)
{
	if (open != 1 && data->line[i] == '$' && data->line[i + 1]
		&& (data->line[i + 1] != '?' && data->line[i + 1] != '$'))
		return (1);
	return (0);
}

int	count_ex(t_pipex *data, int i, int open, int count)
{
	char	*elem;

	elem = NULL;
	while (data->line && data->line[i])
	{
		if (c_e_0(data, i, open))
			c_e_1(data, &elem, &i, open);
		else if (c_e_2(data, i, open))
			c_e_3(data, &elem, &i);
		if (elem)
			c_e_4(&elem, &count);
		if (!data->line[i])
			break ;
		if (handle_open(data, i, &open) && c_e_5(data, i, open))
			break ;
		if (c_e_6(data, i, open))
			count++;
		if (open || (data->line[i] != '$'
				|| (data->line[i] == '$'
					&& is_delim_front(data->line, i + 1))))
			i++;
	}
	return (count);
}
