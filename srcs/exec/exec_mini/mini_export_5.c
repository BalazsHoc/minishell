/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:34:28 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:34:30 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_pwd_2(t_pipex *data)
{
	int	j;

	j = -1;
	while (data->cur_env[++j])
	{
		if (!ft_strncmp(data->cur_env[j], "PWD=", 4))
			return (data->cur_env[j] + 4);
	}
	return (NULL);
}

char	*get_pwd(t_pipex *data)
{
	char	*buf;

	buf = ft_calloc(500, 100, data);
	if (!getcwd(buf, 500 * 100))
		return (free_str(&buf), data->cwd);
	free_str(&data->cwd);
	data->cwd = ft_strdup(data, buf);
	free_str(&buf);
	return (data->cwd);
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

int	malloc_for_list(t_pipex *d, int count)
{
	int	i;

	i = 0;
	while (d->export[i])
		i++;
	d->buf_array = ft_calloc(sizeof(char *), count + i + 1, d);
	return (i);
}

void	set_rest(t_pipex *data, char **buf)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (data->cur_env[++j])
	{
		if (!buf[i])
			buf[i] = data->cur_env[j];
		else
			j--;
		i++;
	}
}
