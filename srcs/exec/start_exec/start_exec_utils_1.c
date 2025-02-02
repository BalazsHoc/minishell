#include "../../../minishell.h"

char	*join_this(char *s1, char *s2, t_pipex *data)
{
	int		i;
	int		j;
	char	*new;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!s2)
		return (free_str(&s1), NULL);
	if (i + j == 0)
		return (NULL);
	new = ft_calloc(sizeof(char), (i + j + 1 + 1), data);
	new[i + j] = '\n';
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		new[i++] = s2[j++];
	free_str(&s1);
	return (new);
}

char	*get_val(t_pipex *data, char *cur)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (cur[k] && is_char(cur[k]))
		k++;
	while (data->cur_env[++i])
	{
		j = 0;
		while (data->cur_env[i][j] && data->cur_env[i][j] != '=')
			j++;
		if (!ft_strncmp(data->cur_env[i], cur, bigger_one_2(j, k)))
			return (ft_strdup(data, data->cur_env[i] + j + 1));
	}
	return (NULL);
}

int	get_input_2(t_pipex *data, int index_1, int i)
{
	int		k;
	int		j;
	char	*new;

	k = 0;
	j = 2;
	while (data->line[data->here_2 - j]
		&& !is_d_b(data->line, data->here_2 - j, 0))
		j++;
	new = ft_calloc(sizeof(char), (((data->here_2 - (j + 1)
						- data->here_2_old) + 1) + 1), data);
	while (k < (data->here_2 - (j + 1) - data->here_2_old) + 1)
	{
		new[k] = data->line[data->here_2_old + k];
		k++;
	}
	data->l[index_1]->input[i] = new;
	return (1);
}

char	*get_input(t_pipex *data, int index_1, int index_2, int index_3)
{
	char	*buf;
	char	*key;
	char	*input;

	g_signal = 0;
	key = data->l[index_1]->cmnds[index_2][index_3 + 1];
	input = NULL;
	buf = readline("> ");
	while (buf && !g_signal && (!ft_strcmp_2(buf, key)))
	{
		if (buf[0] != '\0')
		{
			input = join_this(input, buf, data);
			free_str(&buf);
		}
		buf = readline("> ");
	}
	if (!input)
		return (free_str(&buf), ft_strdup(data, ""));
	return (input);
}

int	find_key(t_pipex *data, int index_1, int index_2, int index_3)
{
	int	i;
	int	j;

	i = data->here_2_old;
	if (i == 0 || !data->line[i - 1] || !data->line[i] || !data->line[i + 1])
		return (i);
	while (data->line[++i])
	{
		j = 0;
		while (data->line[i + j] && data->l[
				index_1]->cmnds[index_2][index_3][j]
			&& data->line[i + j] == data->l[
					index_1]->cmnds[index_2][index_3][j])
			j++;
		if (!data->l[index_1]->cmnds[index_2][index_3][j]
			&& (!data->line[i + j] || data->line[i + j] == '\n'
				|| is_space(data->line[i + j])))
			return (data->here_2 = i + j + 1, i + j + 1);
	}
	return (data->here_2_old);
}
