/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:33:03 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:33:04 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	mini_exit_close_childs(t_pipex *d, int i_1, int i_2)
{
	close_children_pipe(d, &d->fd_in);
	close_pipe(d, &d->fd_out);
	cl_chi_pipes(d, i_1, i_2);
	er_c(d);
}

int	only_dec(char *str)
{
	int	i;
	int	check;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	check = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i] && check < i)
		return (1);
	return (0);
}

int	is_overflow_continue(char *str, int sign)
{
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result > 100000000000000000 && str[i + 1])
			|| (result > 922337203685477580)
			|| (result == 922337203685477580 && (str[i] == '8'
					|| str[i] == '9') && sign == 1)
			|| (result == 922337203685477580 && str[i] == '9' && sign == -1))
			return (1);
		result = result * (unsigned long long)10
			+ (unsigned long long)(str[i] - '0');
		i++;
	}
	return (0);
}

char	*ft_strtrim_3(char *s1, char const *set, t_pipex *data)
{
	int		i;
	int		j;
	int		k;

	if (!s1 || !*s1 || !set || !*set)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = 0;
	while (s1[i + j] && !is_space(s1[i + j]))
		j++;
	k = 0;
	while (s1[i + j + k] && is_space(s1[i + j + k]))
		k++;
	if (k && s1[i + j + k])
		return (s1);
	j--;
	while (j != 0 && ft_strchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j + 1, data));
}

int	is_overflow(t_pipex *data, int index_1, int index_2)
{
	int		i;
	int		sign;
	char	*nptr;

	i = 0;
	sign = 1;
	if (!*data->l[index_1]->ops[index_2][1])
		return (0);
	data->l[index_1]->ops[index_2][1]
		= ft_strtrim_3(data->l[index_1]->ops[index_2][1], " /t/b/v/f/r", data);
	nptr = data->l[index_1]->ops[index_2][1];
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] == '0')
		i++;
	if (ft_strlen(nptr + i) > 19)
		return (1);
	return (is_overflow_continue(nptr + i, sign));
}
