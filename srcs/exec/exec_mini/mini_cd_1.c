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

char	*get_pwd(t_pipex *data)
{
	int	i;

	i = -1;
	if (!data->cur_env)
		return (NULL);
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "PWD=", 4))
			return (data->cur_env[i]);
	}
	return (NULL);
}

void	print_cd_err(int errnum, char *str)
{
	write(2, "bash: cd: ", 11);
	write(2, str, ft_strlen(str));
	if (errnum == ENOENT)
		write(2, ": No such file or directory\n", 29);
	else if (errnum == ENOTDIR)
		write(2, ": Not a directory\n", 19);
	else if (errnum == EACCES)
		write(2, ": Permission denied\n", 21);
	else if (errnum == ENOMEM)
		write(2, ": Cannot allocate memory\n", 26);
	else
		write(2, ": failed\n", 10);
}

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

void	update_env_2(t_pipex *data, int index_1, int index_2)
{
	int		j;
	char	*buf_1;
	char	*buf_2;

	buf_1 = NULL;
	buf_2 = NULL;
	data->buf_str = get_old(data, index_1, index_2);
	if (!data->buf_str)
		return ;
	if (chdir(data->buf_str + 7) == -1)
		print_cd_err(errno, data->buf_str + 7);
	j = 0;
	while (data->buf_str[j] && data->buf_str[j] != '=')
		j++;
	buf_1 = ft_strjoin("PWD", data->buf_str + j, data);
	data->buf_str = get_pwd(data);
	j = 0;
	while (data->buf_str && data->buf_str[j] && data->buf_str[j] != '=')
		j++;
	if (data->buf_str)
		buf_2 = ft_strjoin("OLDPWD", data->buf_str + j, data);
	data->buf_str = NULL;
	update_env_2_continue(data, buf_1, buf_2);
}

void	cd_cmnd(char **argv, t_pipex *data, int index_1, int index_2)
{
	char	*home_dir;

	if (data->l[index_1]->ops[index_2][0]
		&& data->l[index_1]->ops[index_2][1]
			&& data->l[index_1]->ops[index_2][2])
		return (write(2, "bash: cd: ", 11),
			write(2, "too many arguments\n", 20),
			exit_child(data, index_1, index_2, 1));
	home_dir = get_home(data);
	if (!ft_strncmp(argv[1], ".", 2) && home_dir)
		return (update_env(data, index_1, index_2));
	if (!ft_strncmp(argv[1], "-", 2))
		return (update_env_2(data, index_1, index_2));
	if (!argv[1])
	{
		if (chdir(home_dir) == -1)
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
