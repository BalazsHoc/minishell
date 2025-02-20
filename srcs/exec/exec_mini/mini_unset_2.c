/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:34:58 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:35:00 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*key_this(t_pipex *data, char *s)
{
	int		i;
	char	*key;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), (i + 1), data);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		key[i] = s[i];
		i++;
	}
	return (key);
}

int	count_unset_env(t_pipex *data, int index_1, int index_2)
{
	int		i;
	int		j;
	int		k;
	char	*key;

	i = -1;
	k = 0;
	while (data->l[index_1]->ops[index_2][++i + 1])
	{
		j = 0;
		while (data->cur_env[j])
		{
			key = key_this(data, data->cur_env[j]);
			if (ft_strncmp(data->l[index_1]->ops[index_2][i + 1], "_", 2)
				&& !ft_strncmp(data->l[index_1]->ops[index_2][i + 1], key,
					bigger_one(data->l[index_1]->ops[index_2][i + 1], key)))
				k++;
			j++;
			free_this(&key);
		}
	}
	if (k == 0)
		return (-1);
	return (j - k);
}

int	count_unset_export(t_pipex *data, int index_1, int index_2)
{
	int		i;
	int		j;
	int		k;
	char	*key;

	i = -1;
	k = 0;
	while (data->l[index_1]->ops[index_2][++i + 1])
	{
		j = 0;
		while (data->export[j])
		{
			key = key_this(data, data->export[j]);
			if (ft_strncmp(data->l[index_1]->ops[index_2][i + 1], "_", 2)
				&& !ft_strncmp(data->l[index_1]->ops[index_2][i + 1], key,
					bigger_one(data->l[index_1]->ops[index_2][i + 1], key)))
				k++;
			j++;
			free_this(&key);
		}
	}
	if (k == 0)
		return (-1);
	return (j - k);
}

char	**malloc_unset(t_pipex *data, int index_1, int index_2)
{
	int	count;

	count = count_unset_env(data, index_1, index_2);
	if (!data->l[index_1]->ops[index_2][1])
		return (NULL);
	if (count == -1)
		return (NULL);
	return (ft_calloc(sizeof(char *), (count + 1), data));
}

char	**malloc_unset_export(t_pipex *data, int index_1, int index_2)
{
	int	count;

	count = count_unset_export(data, index_1, index_2);
	if (!data->l[index_1]->ops[index_2][1])
		return (NULL);
	if (count == -1)
		return (NULL);
	return (ft_calloc(sizeof(char *), (count + 1), data));
}
