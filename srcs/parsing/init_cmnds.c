#include "../../minishell.h"


void	ft_strncpy_2(char *dest, char *src, int size, int open)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// printf("OPEN : %d\n", open);
	while (j < size)
	{
		while (((!open && is_quote(src[i]))
			|| (open == 1 && is_quote_one(src[i]))
			|| (open == 2 && is_quote_two(src[i])))
			 && !is_space(src[i - 1]))
			i++;
		dest[j] = src[i];
		// printf("DEST: %c\n", dest[j]);
		i++;
		j++;
	}
}

int	count_key(char *line, int j, int open)
{
	int k;
	int check;

	k = 0;
	check = 0;
	while (line[j])
	{
		// printf("COUNT KEY POS: %s CHECK: %d\n", line + j, check);
		if (check && open == 2 && (is_space(line[j]) || line[j] == '\n' || is_quote(line[j])))
			break;
		if (check && !open && (!line[j] || is_space(line[j]) || line[j] == '\n'
			|| is_real_pipe(line, j)
			|| is_red_clean(line, j)
			|| is_quote(line[j])))
			break;
		if (check)
			k++;
		// printf("KEY ______ %d\n", k);
		if (line[j] == '$')
			check = 1;
		j++;
	}
	// printf("COUNT KEY: %d\n", k);
	return (k);
}

char *extract_key(t_pipex *data, int j, int open, int check)
{
	int k;
	char *key;

	key = malloc(sizeof(char) * (count_key(data->line, j, open) + 1));
	if (!key)
		return (error_code(data), NULL);
	key[count_key(data->line, j, open)] = 0;
	k = 0;
	while (data->line[j])
	{
		// printf("OPEN: %d at %s\n", open, line + j);
		if (check && open == 2 && (is_space(data->line[j]) || data->line[j] == '\n' || is_quote(data->line[j])))
			break;
		if (check && !open && (!data->line[j] || is_space(data->line[j]) || data->line[j] == '\n'
			|| is_real_pipe(data->line, j)
			|| is_red_clean(data->line, j)
			|| is_quote(data->line[j])))
			break;
		if (check)
			key[k++] = data->line[j];
		if (data->line[j] == '$')
			check = 1;
		j++;
	}
	return (key);
}

char *fill_key(t_pipex *data, char *str)
{
	int i;
	char *new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (error_code(data), NULL);
	new[ft_strlen(str)] = 0;
	i = -1;
	while (str[++i])
		new[i] = str[i];
	return (new);
}

int	count_expansion(char *line, int i, char *elem, int open)
{
	int count;

	count = ft_strlen(elem);
	// printf("COUNT ELEM: %d\n", count);
	while (line[i])
	{
		// if (line[i] == '$' && elem)
		// 	i += ft_strlen(elem) - 2;
		// printf("POS1: %s\n", line + i);
		if (line[i] == '$')
			i += count_chars(line, i, 0);
		// printf("POS2: %s\n", line + i);
		if (!line[i])
			break;
		if (open == 2 && is_quote_two(line[i]))
			break;
		if (!open && (!line[i] || is_space(line[i]) || line[i] == '\n'
			|| is_real_pipe(line, i)
			|| is_red_clean(line, i)
			|| (is_space(line[i]) && is_quote(line[i + 1]))
			|| ((!line[i + 2] || is_space(line[i + 2]) || line[i + 2] == '\n') && is_quote(line[i + 1]))))
			break;
		count++;
		i++;
	}
	// printf("COUNT EXPANSION: %d\n", count);
	return (count);
}

char	*expand_it(t_pipex *data, int i, int open, char **env)
{
	int j;
	char *key;
	char *elem;
	char *new;

	j = -1;
	elem = NULL;
	// if (line[i] != '$' && line[i - 1])
	// 	i--;
	key = extract_key(data, i, open, 0);
	if (!ft_strncmp(key, "?", 2))
		return (free_str(key), ft_itoa(data->exit_code));
	while (env[++j])
	{
		if (!ft_strncmp(key, env[j], ft_strlen(key) - 1) && env[j][ft_strlen(key)] == '=' && free_this(key))
			elem = fill_key(data, env[j] + (count_key(data->line, i, open) + 1));
	}
	// printf("ELEM $%s$\n", elem);
	new = malloc(sizeof(char) * (count_expansion(data->line, i, elem, open) + 1));
	if (!new)
		return (printf("malloc fail\n"), free_str(elem), error_code(data), NULL);
	new[count_expansion(data->line, i, elem, open)] = 0;
	j = 0;
	while (data->line[i])
	{
		if (data->line[i] == '$')
		{
			ft_strncpy_2(new + j, elem, ft_strlen(elem), open);
			i += count_chars(data->line, i, 0);
			j += ft_strlen(elem);
		}
		if (open && is_quote_two(data->line[i]))
			break;
		if (!open && (!data->line[i + 1] || is_space(data->line[i + 1]) || data->line[i + 1] == '\n'
			|| is_real_pipe(data->line, i + 1)
			|| is_red_clean(data->line, i)
			|| is_quote(data->line[i + 1])))
			// || ((!line[i + 2] || is_space(line[i + 2]) || line[i + 2] == '\n') && is_quote(line[i + 1]))))
			break;
		// printf("POS NEW: %s$\n", data->line + i);
		new[j] = data->line[i++];
		j++;
	}
	return (free(elem), new);
}

char *fill_normal(t_pipex *data, int j, int open)
{
	char *new;

	new = malloc(sizeof(char) * (count_chars(data->line, j, open) + 1));
	if (!new)
		return (perror("malloc fail\n"), error_code(data), NULL);
	new[count_chars(data->line, j, open)] = 0;
	ft_strncpy_2(new, data->line + j, count_chars(data->line, j, open), open);
	return (new);
}

int dollar_in(char *line, int j, int open)
{
	while (line[j])
	{
		if (open == 2 && is_quote_two(line[j]))
			break;
		if (!open && (!line[j + 1] || is_space(line[j + 1]) || line[j + 1] == '\n'
			|| is_real_pipe(line, j + 1)
			|| (is_red_1(line[j]) && !is_red_1(line[j + 1]))
			|| (is_red_1(line[j + 1]) && !is_space(line[j]) && !is_red_1(line[j]))
			|| (is_space(line[j]) && is_quote(line[j + 1]))
			|| ((!line[j + 2] || is_space(line[j + 2]) || line[j + 2] == '\n') && is_quote(line[j + 1]))))
			break;
		if (line[j] == '$')
			return (j);
		j++;
	}
	return (0);
}

char	**fill_cmnds(char **arr, t_pipex *data, int i, char **env)
{
	int	j;
	int k;
	int	index;
	int open;

	j = -1;
	index = -1;
	open = 0;
	k = -i;
	while (data->line[++j] && i >= 0)
	{
		if (is_quote_one(data->line[j]) && is_space(data->line[j - 1]) && !open && ++j)
			open = 1;
		else if (is_quote_two(data->line[j]) && is_space(data->line[j - 1]) && !open && ++j)
			open = 2;
		else if (((is_quote_one(data->line[j]) && open == 1) || (is_quote_two(data->line[j]) && open == 2)) && ++j)
			open = 0;
		// // "this is 'hi there ' last word "
		// printf("FILL_CMNDS: %s | OPEN: %d | K: %d\n", line + j, open, k);
		if (k == 0 && !is_real_pipe(data->line, j) && ((j == 0 && !is_space(data->line[j]))
				|| (is_space(data->line[j - 1]) && !is_space(data->line[j]) && !open)
				|| ((open == 1 && is_quote_one(data->line[j - 1])) || (open == 2 && is_quote_two(data->line[j - 1])))
				|| (is_red_clean(data->line, j) && !open)
				|| ((is_red_in(data->line[j - 1]) && is_red_out(data->line[j])) || (is_red_out(data->line[j - 1]) && is_red_in(data->line[j])))
				|| (is_red_1(data->line[j - 1]) && !is_red_1(data->line[j]) && !is_space(data->line[j]) && data->line[j] != '|' && !open)
				|| ((is_real_pipe(data->line, j - 1)
					|| (data->line[j - 1] == '|' && data->line[j - 2] == '>')) && !is_space(data->line[j]))))
				// && (!open || ((open == 1 && is_quote_one(line[j - 1])) || (open == 2 && is_quote_two(line[j - 1])))))
		{
			// printf("TRUE!\n");
			if (dollar_in(data->line, j, open) && open != 1
				&& (index == -1 || (index >= 0 && ft_strncmp(arr[index], "<<", 3))))
				arr[++index] = expand_it(data, j, open, env);
			// else if (line[dollar_in(line, j, open) + 1] != '?')
			// 	arr[++index] = echo_exit_code();
			else
				arr[++index] = fill_normal(data, j, open);
			if (!arr[index])
				error_code(data);
			// j += count_chars(line, j, open) - 1;
		}
		// printf("I1: %d\n", i);
		if (is_real_pipe(data->line, j) && j > 0 && !is_red_1(data->line[j - 1]) && k++ != INT_MIN)
			i--;
		if (!data->line[j])
			break;
		// printf("I2: %d\n", i);
	}
	return (arr);
}
