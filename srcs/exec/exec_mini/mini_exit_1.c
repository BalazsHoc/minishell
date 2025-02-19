/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:32:48 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:32:50 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	exit_cmnd_util_1(t_pipex *data, int index_1, int index_2)
{
	write(2, "bash: exit: ", 13);
	write(2, data->l[index_1]->ops[index_2][1],
		ft_strlen(data->l[index_1]->ops[index_2][1]));
	write(2, ": numeric argument required\n", 29);
	errno = 2;
	er_c(data);
}

int	exit_cmnd_util_2(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->ops[index_2][1]
		&& data->l[index_1]->ops[index_2][0]
			&& data->l[index_1]->ops[index_2][2]
			&& data->last_exit_status == 0)
		return (1);
	return (0);
}

int	exit_cmnd_util_3(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->ops[index_2][1]
		&& data->l[index_1]->ops[index_2][0]
		&& data->l[index_1]->ops[index_2][2])
		return (1);
	return (0);
}

void	exit_cmnd(t_pipex *data, int index_1, int index_2)
{
	long long	i;

	i = 0;
	printf("exit\n");
	if (data->l[index_1]->ops[index_2][1])
	{
		if (is_overflow(data, index_1, index_2)
			|| !only_dec(data->l[index_1]->ops[index_2][1]))
			return (exit_cmnd_util_1(data, index_1, index_2));
		i = ft_atoi(data->l[index_1]->ops[index_2][1]);
		if (i > 255 || i < 0)
			i = i % 256;
		errno = i;
	}
	if (exit_cmnd_util_2(data, index_1, index_2))
		return (write(2, "bash: exit: too many arguments\n", 32),
			errno = 1, exit_child(data, index_1, index_2, 1));
	else if (exit_cmnd_util_3(data, index_1, index_2))
		return (write(2, "bash: exit: too many arguments\n", 32),
			exit_child(data, index_1, index_2, data->last_exit_status));
	else
		return (data->last_exit_status = errno, er_c(data));
}

void	exit_cmnd_child(t_pipex *d, int i_1, int i_2)
{
	long long	i;

	i = 0;
	if (!d->l[i_1]->ops || !d->l[i_1]->ops[i_2])
		return ;
	if (d->l[i_1]->ops[i_2][1])
	{
		i = ft_atoi(d->l[i_1]->ops[i_2][1]);
		if (is_overflow(d, i_1, i_2)
			|| !only_dec(d->l[i_1]->ops[i_2][1]))
			return (write(2, "bash: exit: ", 13),
				write(2, d->l[i_1]->ops[i_2][1],
				ft_strlen(d->l[i_1]->ops[i_2][1])),
				write(2, ": numeric argument required\n", 29),
				errno = 2, mini_exit_close_childs(d, i_1, i_2));
		if (i > 255 || i < 0)
			i = i % 256;
		errno = i;
	}
	if (d->l[i_1]->ops[i_2]
		&& d->l[i_1]->ops[i_2][1]
		&& d->l[i_1]->ops[i_2][2])
		return (write(2, "bash: exit: too many arguments\n", 32),
			errno = 1, mini_exit_close_childs(d, i_1, i_2));
	return (d->last_exit_status = errno, mini_exit_close_childs(d, i_1, i_2));
}
