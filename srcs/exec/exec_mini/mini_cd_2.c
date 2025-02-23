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

void	update_env_continue(t_pipex *d, int index_1, int index_2, char *buf)
{
	char	*cur_pwd;

	d->buf_int = -1;
	cur_pwd = get_pwd(d);
	while (d->cur_env[++d->buf_int])
	{
		if (!ft_strncmp(d->cur_env[d->buf_int], "PWD=", 4))
		{
			if (!ft_strncmp(d->l[index_1]->ops[index_2][1], ".", 1)
				&& buf && !*buf)
			{
				if (free_this(&buf) && cur_pwd[ft_strlen(cur_pwd) - 1] != '/')
					buf = ft_strjoin("/", d->l[index_1]->ops[index_2][1], d);
				else
					buf = ft_strjoin(NULL, d->l[index_1]->ops[index_2][1], d);
				cur_pwd = ft_strjoin(cur_pwd, buf, d);
				free_this(&d->cur_env[d->buf_int]);
				d->cur_env[d->buf_int] = ft_strjoin("PWD=", cur_pwd, d);
				free_str(&cur_pwd);
			}
			else if (free_this(&d->cur_env[d->buf_int]) && buf && *buf)
				d->cur_env[d->buf_int] = ft_strjoin("PWD=", buf, d);
			free_str(&buf);
		}
	}
}

void	update_cwd(t_pipex *d, int index_1, int index_2, char *buf)
{
	char	*buf2;

	buf2 = NULL;
	get_pwd(d);
	if (!ft_strncmp(d->l[index_1]->ops[index_2][1], ".", 1)
		&& buf && !*buf)
	{
		buf2 = ft_strjoin("/", d->l[index_1]->ops[index_2][1], d);
		buf = d->cwd;
		if (d->cwd[ft_strlen(d->cwd) - 1] != '/')
			d->cwd = ft_strjoin(d->cwd, buf2, d);
		else
			d->cwd = ft_strjoin(d->cwd, d->l[index_1]->ops[index_2][1], d);
		free_str(&buf);
	}
	else if (buf && *buf)
	{
		buf2 = d->cwd;
		d->cwd = ft_strdup(d, buf);
	}
	free_str(&buf2);
}

void	put_old_pwd(t_pipex *data)
{
	int		i;
	char	**arr;

	i = 0;
	while (data->cur_env[i])
		i++;
	arr = ft_calloc(sizeof(char *), i + 1 + 1, data);
	i = -1;
	while (data->cur_env[++i])
		arr[i] = ft_strdup(data, data->cur_env[i]);
	arr[i] = ft_strjoin("OLDPWD=", data->cwd, data);
	free_list(data->cur_env);
	data->cur_env = arr;
	i = -1;
	while (data->export[++i])
	{
		if (!ft_strncmp(data->export[i], "OLDPWD", 6))
		{
			free_str(&data->export[i]);
			data->buf_str = ft_strjoin(data->cwd, "\"", data);
			data->export[i] = ft_strjoin("OLDPWD=\"", data->buf_str, data);
			free_str(&data->buf_str);
		}
	}
}

void	update_env_inbtween(t_pipex *d, int i_1, int index_2, char *buf)
{
	buf = ft_calloc(sizeof(char), (500 * 100), d);
	if (!getcwd(buf, 500 * 100) && errno == ENOENT
		&& write(2, "cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 109))
		d->l[i_1]->exit_codes[index_2] = 0;
	update_cwd(d, i_1, index_2, buf);
	update_env_continue(d, i_1, index_2, buf);
	get_pwd(d);
	free_str(&buf);
}

void	update_env(t_pipex *d, int i_1, int index_2)
{
	int		i;
	char	*buf;
	char	*cur_pwd;

	i = -1;
	buf = NULL;
	cur_pwd = get_pwd_2(d);
	while (d->cur_env[++i])
	{
		if (!ft_strncmp(d->cur_env[i], "OLDPWD=", 7))
		{
			if (!cur_pwd && cut_out_old(d))
			{
				i = -1;
				break ;
			}
			buf = d->cur_env[i];
			d->cur_env[i] = ft_strjoin("OLDPWD=", cur_pwd, d);
		}
	}
	if (!cur_pwd && !buf && i != -1)
		put_old_pwd(d);
	free_str(&buf);
	update_env_inbtween(d, i_1, index_2, NULL);
}
