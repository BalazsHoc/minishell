/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_is_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:53:25 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:53:26 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_char(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == '_' || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	is_red_clean(char *str, int index)
{
	int	check;

	check = -1;
	if (!is_red_1(str[index]))
		return (0);
	if (index == 0)
		return (1);
	while (index - ++check >= 0 && is_red_in(str, index - check))
		continue ;
	if (check == 0)
		check = -1;
	if (check == 1)
		return (1);
	if (check < 0)
	{
		while (index - ++check >= 0 && is_red_out(str, index - check))
			continue ;
	}
	if (check % 2 != 0)
		return (1);
	return (0);
}

int	is_executable(t_pipex *data, int index_1, int index_2)
{
	char	*str;

	str = data->l[index_1]->ops[index_2][0];
	if (!str)
		return (0);
	if (str[0] == '.' && (!str[1] || str[1] == '/' || str[1] == '.'))
		return (1);
	if (!ft_strncmp(str, "/", 2))
		return (1);
	return (0);
}

int	check_executable(t_pipex *data, int index_1, int index_2)
{
	char	*str;

	str = data->l[index_1]->ops[index_2][0];
	if (!str)
		return (0);
	if (str[0] == '.' && !str[1])
		return (write(2, "bash: .: filename argument required\n", 37),
			exit_child(data, index_1, index_2, 2), 0);
	if (!ft_strncmp(str, "..", 3))
		return (0);
	if (!ft_strncmp(str, "/", 2))
		return (0);
	if (access(str, X_OK))
	{
		if (errno == EACCES)
		{
			write(2, "bash: ", 7);
			write(2, str, ft_strlen(str));
			write(2, ": Permission denied\n", 21);
			exit_child(data, index_1, index_2, 126);
		}
		return (0);
	}
	data->l[index_1]->binary[index_2] = 1;
	return (1);
}
