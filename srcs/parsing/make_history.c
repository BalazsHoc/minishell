/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:52:01 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:52:02 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_old(t_pipex *data, int index_1, int index_2, int index_3)
{
	int	k;

	k = 0;
	while (data->line[data->l[index_1]->pos_in_line[index_2][index_3] + k]
		&& data->line[data->l[
				index_1]->pos_in_line[index_2][index_3] + k] != '\n')
		k++;
	if (data->line[data->l[index_1]->pos_in_line[index_2][index_3] + k] == '\n')
		k++;
	data->here_2_old = data->l[index_1]->pos_in_line[index_2][index_3] + k;
}

int	count_nl(t_pipex *data, int i)
{
	while (data->line[++i] && data->line[i] != '\n')
		i++;
	return (i);
}

// void	make_history(t_pipex *data, int i)
// {
// 	char	*new;
// 	int		j;

// 	data->buf_int = 0;
// 	printf("I1: %d\n", i);
// 	if (i == 0)
// 	{
// 		i = count_nl(data);
// 		data->buf_int = data->here_2_old;
// 		printf("buf1111 INT: %d\n", data->buf_int);
// 	}
// 	printf("I2: %d\n", i);
// 	printf("buf INT: %d\n", data->buf_int);
// 	new = ft_calloc(sizeof(char), (i + 1), data);
// 	j = -1;
// 	while (++j < i)
// 		new[j] = data->line[data->buf_int + j];
// 	printf("NEW: %s\n", new);
// 	add_history(new);
// 	free_str(&new);
// }

void	make_history(t_pipex *data)
{
	char	*new;
	int		k;
	int		j;
	int		i;

	i = -1;
	while (data->line[++i])
	{
		k = 0;
		while (data->line[i + k] && data->line[i + k] != '\n')
			k++;
		new = ft_calloc(sizeof(char), (k + 1), data);
		j = -1;
		while (++j < k)
			new[j] = data->line[i + j];
		i += k;
		// printf("NEW: %s\n", new);
		add_history(new);
		free_str(&new);
		if (!data->line[i])
			break ;
	}
}

// void	make_history(t_pipex *data, int index_1, int check, int check_2)
// {
// 	int this;

// 	this = 0;
// 	if (check < 0)
// 		make_history_3(data, 0);
// 	else
// 	{
// 		printf("CHECK THIS1: here_2: %d | here_2_old: %d check: %d\n", data->here_2, data->here_2_old, check);
// 		data->buf_int = data->here_2_old;
// 		if (data->here_2 && ++this)
// 		{
// 			set_old(data, index_1, check_2, check);
// 		}
// 		printf("CHECK THIS2: here_2: %d | here_2_old: %d check: %d\n", data->here_2, data->here_2_old, check);
// 		find_key(data, index_1, check_2, check + 1);
// 		if (data->here_2 == data->here_2_old)
// 			check = count_nl(data);
// 		else if (index_1 == 0)
// 			check = -1;
// 			check = data->here_2_old - data->buf_int;
// 		printf("CHECK THIS3: here_2: %d | here_2_old: %d check: %d\n", data->here_2, data->here_2_old, check);
// 		make_history_3(data, check + 1);
// 		data->buf_int = 0;
// 		if (!this && printf("PENIS\n"))
// 			set_old(data, index_1, check_2, check);
// 	}
// // }
void	make_history_2(t_pipex *data, int index_1, int check, int check_2)
{
	int	this;

	this = 0;
	if (check < 0)
		return ;
		// make_history_3(data, 0);
	else
	{
		// printf("CHECK THIS1: here_2: %d | here_2_old: %d check: %d\n", data->here_2, data->here_2_old, check);
		data->buf_int = data->here_2_old;
		if (data->here_2 && ++this)
		{
			set_old(data, index_1, check_2, check);
		}
		// printf("CHECK THIS2: here_2: %d | here_2_old: %d check: %d\n", data->here_2, data->here_2_old, check);
		find_key(data, index_1, check_2, check + 1);
		// if (index_1 == 0)
		// 	check = -1;
		// else if (data->here_2 < data->here_2_old)
		// 	check = data->here_2_old - data->buf_int;
		// else
		// 	check = data->here_2 - data->buf_int;
		// printf("CHECK THIS3: here_2: %d | here_2_old: %d check: %d\n", data->here_2, data->here_2_old, check);
		// make_history_3(data, check + 1);
		data->buf_int = 0;
		if (!this)
			set_old(data, index_1, check_2, check);
	}
}

void	handle_here(t_pipex *data, int index_1, int i, int j)
{
	int	check;
	int	check_2;

	check = -1;
	check_2 = -1;
	while (data->l[index_1]->cmnds[++i])
	{
		j = -1;
		while (data->l[index_1]->cmnds[i][++j])
		{
			if (!ft_strncmp(data->l[index_1]->cmnds[i][j], "<<", 3)
				&& !data->l[index_1]->red_cmnd[i][j])
			{
				check = j;
				check_2 = i;
			}
		}
	}
	make_history_2(data, index_1, check, check_2);
}
