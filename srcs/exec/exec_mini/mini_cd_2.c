/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:32:23 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:32:24 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_home(t_pipex *data)
{
	int	i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "HOME=", 5))
			return (data->cur_env[i] + 5);
	}
	return (NULL);
}

char	*get_old(t_pipex *data, int index_1, int index_2)
{
	int	i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7)
			&& printf("%s\n", data->cur_env[i] + 7))
			return (data->cur_env[i]);
	}
	return (write(2, "bash: cd: OLDPWD not set\n", 26),
		exit_child(data, index_1, index_2, 1), NULL);
}

char	*get_path(t_pipex *data)
{
	int	i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "PATH=", 5))
			return (data->cur_env[i]);
	}
	return (0);
}

void	update_env_continue(t_pipex *d, int index_1, int index_2, char *buf)
{
	int		i;
	char	*cur_pwd;

	i = -1;
	cur_pwd = get_pwd(d);
	while (d->cur_env[++i] && i < 100)
	{
		if (!ft_strncmp(d->cur_env[i], "PWD=", 4))
		{
			if (!ft_strncmp(d->l[index_1]->ops[index_2][1], ".", 1)
				&& !*buf && free_this(&buf))
			{
				if (cur_pwd[ft_strlen(cur_pwd) - 1] != '/')
					buf = ft_strjoin("/", d->l[index_1]->ops[index_2][1], d);
				else
					buf = ft_strjoin(NULL, d->l[index_1]->ops[index_2][1], d);
				cur_pwd = ft_strjoin(cur_pwd + 4, buf, d);
				d->cur_env[i] = ft_strjoin("PWD=", cur_pwd, d);
				free_str(&cur_pwd);
			}
			else if (free_this(&d->cur_env[i]))
				d->cur_env[i] = ft_strjoin("PWD=", buf, d);
			free_str(&buf);
		}
	}
}

void	update_env(t_pipex *data, int index_1, int index_2)
{
	int		i;
	char	*buf;
	char	*cur_pwd;

	i = -1;
	buf = NULL;
	cur_pwd = get_pwd(data);
	while (data->cur_env[++i] && i < 100)
	{
		if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7))
		{
			buf = data->cur_env[i];
			data->cur_env[i] = ft_strjoin("OLDPWD=", cur_pwd + 4, data);
			free(buf);
		}
	}
	buf = getcwd(NULL, 0);
	if (!buf)
		return (printf("failed getcwd() !\n"), error_code(data));
	update_env_continue(data, index_1, index_2, buf);
	free_str(&buf);
}
