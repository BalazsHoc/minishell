/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:32:08 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:32:09 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	update_env_2_continue(t_pipex *data, char *buf_1, char *buf_2)
{
	int	i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7) && buf_2)
		{
			free_str(&data->cur_env[i]);
			data->cur_env[i] = NULL;
			data->cur_env[i] = buf_2;
		}
		else if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7) && !buf_2 && buf_1)
		{
			free_str(&data->cur_env[i]);
			data->cur_env[i] = (buf_1);
		}
		else if (!ft_strncmp(data->cur_env[i], "PWD=", 4) && buf_2 && buf_1)
		{
			free_str(&data->cur_env[i]);
			data->cur_env[i] = (buf_1);
		}
	}
}

int	unset_old_export(t_pipex *data)
{
	int		i;
	char	*buf;

	i = -1;
	buf = NULL;
	while (data->export[++i])
	{
		if (!ft_strncmp(data->export[i], "OLDPWD=", 7))
		{
			buf = data->export[i];
			data->export[i] = ft_strdup(data, "OLDPWD");
			free_str(&buf);
		}
	}
	return (1);
}

int	cut_out_old(t_pipex *data)
{
	int		i;
	int		count;
	char	**arr;

	i = -1;
	count = 0;
	while (data->cur_env[++i])
	{
		if (ft_strncmp(data->cur_env[i], "OLDPWD=", 7))
			count++;
	}
	arr = ft_calloc(sizeof(char *), count + 1, data);
	i = -1;
	count = -1;
	while (data->cur_env[++i])
	{
		if (ft_strncmp(data->cur_env[i], "OLDPWD=", 7))
			arr[++count] = ft_strdup(data, data->cur_env[i]);
	}
	free_list(data->cur_env);
	data->cur_env = arr;
	return (unset_old_export(data));
}

void	update_env_2(t_pipex *data, int index_1, int index_2)
{
	char	*buf_1;
	char	*buf_2;

	buf_1 = NULL;
	buf_2 = NULL;
	data->buf_str = get_pwd_2(data);
	buf_1 = ft_strdup(data, get_old(data, index_1, index_2));
	if (!buf_1)
		return ;
	if (data->buf_str)
		buf_2 = ft_strjoin("OLDPWD=", data->buf_str, data);
	else if (cut_out_old(data) && chdir(buf_1) == -1 && free_this(&buf_1))
		return (print_cd_err(errno, data->buf_str + 7));
	if (!data->buf_str && free_this(&buf_1) && get_pwd(data))
		return ;
	if (chdir(buf_1) == -1 && free_this(&buf_1))
		print_cd_err(errno, data->buf_str + 7);
	data->buf_str = buf_1;
	buf_1 = ft_strjoin("PWD=", buf_1, data);
	free_str(&data->buf_str);
	update_env_2_continue(data, buf_1, buf_2);
	get_pwd(data);
}

void	cd_cmnd(char **argv, t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->ops[index_2][0]
		&& data->l[index_1]->ops[index_2][1]
			&& data->l[index_1]->ops[index_2][2])
		return (write(2, "bash: cd: ", 11),
			write(2, "too many arguments\n", 20),
			exit_child(data, index_1, index_2, 1));
	if (!ft_strncmp(argv[1], ".", 2) && data->home)
		return (update_env(data, index_1, index_2));
	if (!ft_strncmp(argv[1], "-", 2))
		return (update_env_2(data, index_1, index_2));
	if (!argv[1])
	{
		if (chdir(data->home) == -1)
			print_cd_err(errno, argv[1]);
		else
			update_env(data, index_1, index_2);
	}
	else if (argv[1] && chdir(argv[1]) == -1)
		return (print_cd_err(errno, argv[1]),
			exit_child(data, index_1, index_2, 1));
	else if (argv[1])
		update_env(data, index_1, index_2);
}
