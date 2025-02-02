#include "../../minishell.h"

int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
}

int	count_reds(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if (is_red(data, index_1, index_2, i))
			count++;
		if (!data->l[index_1]->cmnds[index_2][i + 1])
			break ;
	}
	return (count);
}

int	count_ops(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->l[index_1]->cmnds[index_2][i])
	{
		count++;
		i++;
	}
	return (count - (count_reds(data, index_1, index_2) * 2));
}

void	fill_ops(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		while (data->l[index_1]->cmnds[index_2][i]
			&& is_red(data, index_1, index_2, i))
		{
			i += 2;
			if (!data->l[index_1]->cmnds[index_2][i])
				break ;
		}
		if (data->l[index_1]->cmnds[index_2][i])
		{
			data->l[index_1]->ops[index_2][++j] = ft_calloc(sizeof(char *),
					(ft_strlen(data->l[index_1]->cmnds[index_2][i]) + 1), data);
			ft_strcpy(data->l[index_1]->cmnds[index_2][i], data->l[
				index_1]->ops[index_2][j]);
		}
		else
			break ;
	}
}
