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

char	*ft_strtrim_2(char *str, t_pipex *data)
{
	char	*new;
	int		i;

	i = 0;
	while (is_space(str[i]))
		i++;
	new = ft_strdup(data, str + i);
	free_str(&str);
	return (new);
}

char	*ft_strdup_3(t_pipex *data, char *str)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	k = count_chars_3(str);
	if (!str || !*str)
		return (NULL);
	new = ft_calloc(sizeof(char), (k + 1), data);
	k = 0;
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i + j] == ' ')
			j++;
		if (j)
			new[k++] = ' ';
		i += j;
		if (!str[i])
			break ;
		new[k++] = str[i];
	}
	return (new);
}

int	count_chars_3(char *str)
{
	int	i;
	int	k;
	int	j;

	i = -1;
	k = 0;
	while (str[++i])
	{
		j = 0;
		while (str[i + j] == ' ')
			j++;
		if (j)
			k++;
		i += j;
		if (!str[i])
			break ;
		k++;
	}
	return (k);
}

int	if_exec_cmnds_utils_4(t_pipex *data, int index, int i, int check)
{
	write(2, "bash: ", 6);
	write(2, data->l[index]->cmnds[i][
		first_invalid_in(data, index, i)],
		ft_strlen(data->l[index]->cmnds[i][
			first_invalid_in(data, index, i)]));
	write(2, ": No such file or directory\n", 29);
	if (i > 0 && !ft_strncmp(data->l[index]->paths[i], "pathnfound", 11))
		return (exit_child(data, index, i, 0), 1);
	if (check)
		return (exit_child(data, index, i, 1), 1);
	else
		return (exit_child(data, index, i, 127), 1);
}

int	skip_nl(t_pipex *data)
{
	if (data->here_2 > data->here_2_old)
		data->here_2_old = data->here_2;
	else
		data->here_2 = data->here_2_old;
	while (data->here_2_old < data->chars_in_line
		&& data->line[data->here_2_old]
		&& (data->line[data->here_2_old] == '\n'
			|| is_space(data->line[data->here_2_old])))
	{
		data->here_2++;
		data->here_2_old++;
	}
	return (1);
}
