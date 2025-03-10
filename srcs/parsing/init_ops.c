/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:51:30 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:51:32 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
}

int	count_reds(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if (is_red(data, index_1, index_2, i))
			count = count + 1 + (if_th(data, index_1, index_2, i));
		if (!data->l[index_1]->cmnds[index_2][i + 1])
			break ;
	}
	return (count);
}

int	count_ops(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->l[index_1]->cmnds[index_2][i])
	{
		if (*data->l[index_1]->cmnds[index_2][i]
			|| is_empty_quotes(data, index_1, index_2, i))
			count++;
		i++;
	}
	count = count - (count_reds(data, index_1, index_2) * 2);
	return (count);
}

void	fill_ops(t_pipex *d, int i_1, int i_2, int i)
{
	int	j;

	j = -1;
	while (d->l[i_1]->cmnds[i_2][++i]
		&& j < count_ops(d, i_1, i_2))
	{
		while (d->l[i_1]->cmnds[i_2][i]
			&& is_red(d, i_1, i_2, i))
		{
			i += 2;
			if (!d->l[i_1]->cmnds[i_2][i])
				break ;
		}
		if (d->l[i_1]->cmnds[i_2][i])
		{
			if (*d->l[i_1]->cmnds[i_2][i] || is_empty_quotes(d, i_1, i_2, i))
			{
				d->l[i_1]->ops[i_2][++j] = ft_calloc(sizeof(char *),
						(ft_strlen(d->l[i_1]->cmnds[i_2][i]) + 1), d);
				ft_strcpy(d->l[i_1]->cmnds[i_2][i], d->l[i_1]->ops[i_2][j]);
			}
		}
		else
			break ;
	}
}
