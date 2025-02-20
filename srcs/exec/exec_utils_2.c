/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:58:35 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/18 14:58:37 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_cat_inline(t_pipex *data, int i_1)
{
	int	i;

	i = 0;
	while (data->l[i_1]->cmnds[i]
		&& data->l[i_1]->ops[i] && data->l[i_1]->ops[i][0]
		&& (!ft_strncmp(data->l[i_1]->ops[i][0], "cat", 4)
		|| !ft_strncmp(data->l[i_1]->ops[i][0], "usr/bin/cat", 12)
			|| !ft_strncmp(data->l[i_1]->ops[i][0], "/bin/cat", 9)))
		i++;
	if (i == data->l[i_1]->cmnd_count)
		return (1);
	return (0);
}

