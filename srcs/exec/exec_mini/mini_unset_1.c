#include "../../../minishell.h"

int	unset_env_utils_1(char *str, char *key)
{
	if (ft_strncmp(str, "_", 2)
		&& !ft_strncmp(str, key,
			bigger_one(str, key)))
		return (1);
	return (0);
}

void	unset_env(t_pipex *data, int index_1, int index_2, int i)
{
	int		j;
	int		check;
	char	*key;

	data->buf_array = malloc_unset(data, index_1, index_2);
	if (!data->buf_array)
		return ;
	while (data->cur_env[++i])
	{
		j = -1;
		check = 0;
		key = key_this(data, data->cur_env[i]);
		while (data->l[index_1]->ops[index_2][++j + 1])
		{
			if (unset_env_utils_1(
					data->l[index_1]->ops[index_2][j + 1], key))
				check = 1;
		}
		if (free_this(&key) && !check)
			data->buf_array[data->buf_int++] = data->cur_env[i];
		else
			free_str(&data->cur_env[i]);
	}
	free(data->cur_env);
	data->cur_env = data->buf_array;
}

int	unset_export_utils_1(char *str, char *key)
{
	if (ft_strncmp(str, "_", 2)
		&& !ft_strncmp(str,
			key, bigger_one(str, key)))
		return (1);
	return (0);
}

void	unset_export(t_pipex *data, int index_1, int index_2, int i)
{
	int		j;
	int		check;
	char	*key;

	data->buf_array = malloc_unset(data, index_1, index_2);
	if (!data->buf_array)
		return ;
	while ((++i < 1 || (i > 0 && free_this(&data->buf_str))) && data->export[i])
	{
		j = -1;
		check = 0;
		key = key_this(data, data->export[i]);
		while (data->l[index_1]->ops[index_2][++j + 1])
		{
			if (unset_export_utils_1(
					data->l[index_1]->ops[index_2][j + 1], key))
				check = 1;
		}
		if (free_this(&key) && !check)
			data->buf_array[data->buf_int++] = data->export[i];
		else
			free_this(&data->export[i]);
	}
	data->export = data->buf_array;
}

void	unset_cmnd(t_pipex *data, int index_1, int index_2, int i)
{
	data->buf_int = 0;
	unset_env(data, index_1, index_2, i);
	data->buf_int = 0;
	unset_export(data, index_1, index_2, i);
}
