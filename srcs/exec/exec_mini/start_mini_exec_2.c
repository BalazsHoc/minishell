/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mini_exec_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:35:43 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:35:44 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		printf("%s\n", arr[i++]);
}

int	bigger_one(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (i > j)
		return (i);
	return (j);
}

void	export_display(t_pipex *data)
{
	int	i;

	i = -1;
	while (data->export[++i])
		printf("declare -x %s\n", data->export[i]);
}

void	print_pwd(t_pipex *data)
{
	if (!get_pwd(data))
		return ;
	printf("%s\n", get_pwd(data) + 4);
}
