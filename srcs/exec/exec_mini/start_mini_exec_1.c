/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mini_exec_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:35:33 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:35:34 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_valid_cwd(t_pipex *data)
{
	char	*buf;

	buf = ft_calloc(sizeof(char), (500 * 100), data);
	getcwd(buf, 500 * 100);
	if (!buf)
		return (perror("getcwd() failed!"), -1);
	if (!*buf)
		return (free_str(&buf), 0);
	return (free_str(&buf), 1);
}

void	print_update_env(t_pipex *data, int index_1, int index_2)
{
	int		i;
	char	*buf_1;
	char	*buf_2;

	i = -1;
	buf_1 = NULL;
	buf_2 = NULL;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "_=", 2))
		{
			buf_1 = data->cur_env[i];
			if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "env", 4))
				buf_2 = ft_strdup(data, "/usr/bin/env");
			else
				buf_2 = ft_strdup(data, data->l[index_1]->ops[index_2][0]);
			data->cur_env[i] = ft_strjoin("_=", buf_2, data);
			free_str(&buf_1);
			free_str(&buf_2);
			break ;
		}
	}
	print_list(data->cur_env);
}

void	mini_parent(t_pipex *data, int index_1, int index_2)
{
	if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "cd", 3))
		cd_cmnd(data->l[index_1]->ops[index_2], data, index_1, index_2);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "export", 7)
		&& data->l[index_1]->ops[index_2][1])
		export_update(data, index_1, index_2, -1);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "env", 4)
	|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/env", 9)
	|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/env", 13))
		print_update_env(data, index_1, index_2);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "unset", 6))
		unset_cmnd(data, index_1, index_2, -1);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "exit", 5))
		exit_cmnd(data, index_1, index_2);
}

void	parent_child(t_pipex *data, int index_1, int index_2)
{
	errno = 0;
	if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "export", 7)
		&& !data->l[index_1]->ops[index_2][1])
		export_display(data);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "pwd", 4)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/pwd", 9)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/pwd", 13))
		print_pwd(data);
}

void	mini_child(t_pipex *data, int index_1, int index_2)
{
	errno = 0;
	if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "cd", 3))
		cd_cmnd(data->l[index_1]->ops[index_2], data, index_1, index_2);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "export", 7)
		&& data->l[index_1]->ops[index_2][1])
		export_update(data, index_1, index_2, -1);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "export", 7)
		&& !data->l[index_1]->ops[index_2][1])
		export_display(data);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "env", 4)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/env", 9)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/env", 13))
		print_update_env(data, index_1, index_2);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "unset", 6))
		unset_cmnd(data, index_1, index_2, -1);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "pwd", 4)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/pwd", 9)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/pwd", 13))
		print_pwd(data);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "exit", 5))
		exit_cmnd_child(data, index_1, index_2);
	else if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "ls", 3)
		&& !is_valid_cwd(data))
		printf("\n");
}
