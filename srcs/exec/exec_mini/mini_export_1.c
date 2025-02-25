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

int	isv(t_pipex *data, int index_1, int index_2, int i)
{
	int		j;
	char	*str;

	j = -1;
	str = data->l[index_1]->ops[index_2][i];
	while (str[++j] && str[j] != '=')
	{
		if (!is_char(str[j])
			|| (j == 0 && !((str[j] >= 65 && str[j] <= 90)
					|| (str[j] >= 97 && str[j] <= 122)
					|| str[j] == '_' || str[j] == '$' || str[j] == '?')))
			return (0);
	}
	if (str[j] && j == 0)
		return (0);
	return (j);
}

void	ex_u_util_2(t_pipex *data, int index_1, int index_2, int i)
{
	write(2, "bash: export: `", 16);
	write(2, data->l[index_1]->ops[index_2][i],
		ft_strlen(data->l[index_1]->ops[index_2][i]));
	write(2, "': not a valid identifier\n", 27);
	exit_child(data, index_1, index_2, 1);
}

int	ex_u_util_1(t_pipex *data, char *str)
{
	if (has_equal(str) && ft_strncmp(str, "_=", 2)
		&& already_there(data, str) == -1)
		return (1);
	return (0);
}

void	export_update(t_pipex *data, int index_1, int index_2, int i)
{
	int	count;
	int	count_export;

	count = 0;
	count_export = 0;
	while (data->l[index_1]->ops[index_2][1 + ++i])
	{
		if (isv(data, index_1, index_2, i + 1))
		{
			if (ex_u_util_1(data, data->l[index_1]->ops[index_2][1 + i])
				&& is_it_last(data, index_1, index_2, i + 1))
				count++;
			else if (ft_strncmp(data->l[index_1]->ops[index_2][1 + i], "_=", 2)
				&& is_there_2(data, data->l[index_1]->ops[
					index_2][1 + i]) == -1)
				count_export++;
		}
		else
			ex_u_util_2(data, index_1, index_2, 1 + i);
	}
	// printf("COUNT: %d | %d\n", count, count_export);
	export_env(data, index_1, index_2, count);
	update_export(data, index_1, index_2, count + count_export);
}
