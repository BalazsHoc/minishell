/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:33:22 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:33:23 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ex_u_util_1(char *str, int j)
{
	if (str[j] && str[j] != '=')
		return (1);
	return (0);
}

int	ex_u_util_2(char *str, int j, int enf_of_while)
{
	if (!enf_of_while)
	{
		if (j == 0 && !((str[j] >= 65 && str[j] <= 90)
				|| (str[j] >= 97 && str[j] <= 122)
				|| str[j] == '_'))
			return (1);
		else if (!is_char(str[j]))
			return (1);
	}
	else if (str[j] && j == 0)
		return (1);
	return (0);
}

void	ex_u_util_3(t_pipex *data, int index_1, int index_2)
{
	write(2, "bash: export: `", 16);
	write(2, data->l[index_1]->ops[index_2][1],
		ft_strlen(data->l[index_1]->ops[index_2][1]));
	write(2, "': not a valid identifier\n", 27);
	exit_child(data, index_1, index_2, 1);
}

int	ex_u_util_4(t_pipex *data, char *str, int j)
{
	if (str[j] && ft_strncmp(str, "_=", 2) && already_there(data, str) == -1)
		return (1);
	return (0);
}

void	export_update(t_pipex *data, int index_1, int index_2, int i)
{
	int	j;
	int	count;
	int	count_export;

	count = 0;
	count_export = 0;
	while (data->l[index_1]->ops[index_2][1 + ++i])
	{
		j = -1;
		while (ex_u_util_1(data->l[index_1]->ops[index_2][1 + i], ++j))
		{
			if (ex_u_util_2(data->l[index_1]->ops[index_2][1 + i], j, 0))
				return (ex_u_util_3(data, index_1, index_2));
		}
		if (ex_u_util_2(data->l[index_1]->ops[index_2][1 + i], j, 1))
			return (ex_u_util_3(data, index_1, index_2));
		else if (ex_u_util_4(data, data->l[index_1]->ops[index_2][1 + i], j))
			count++;
		else if (ft_strncmp(data->l[index_1]->ops[index_2][1 + i], "_=", 2)
			&& is_there_2(data, data->l[index_1]->ops[index_2][1 + i]) == -1)
			count_export++;
	}
	export_env(data, index_1, index_2, count);
	update_export(data, index_1, index_2, count + count_export);
}
