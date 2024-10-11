/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:41:53 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/11 15:41:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_code()
{
	printf("\n");
}

int count_cmnds(char *line)
{
	int count;
	int i;

	count = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			i++;
		if (line[i] == '|' )
			count++;
		i++;
	}
	return (count);
}

int is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int count_elem(char *line, int i)
{
	int count;
	int j;
	int k;

	count = 0;
	j = 0;
	k = -i;
	while (line[j] && i >= 0)
	{
		if (k == 0 && j > 0 && !is_space(line[j])
			&& is_space(line[j - 1]) && line[j] != '|')
			count++;
		else if (k == 0 && j == 0 && !is_space(line[j]))
			count++;
		if (line[j] == '|')
		{
			i--;
			k++;
		}
		j++;
	}
	return (count);
}

int count_chars(char *line)
{
	int count;

	count = 0;
	while (line[count])
	{
		if (is_space(line[count]))
			break;
		count++;
	}
	return (count);
}

char **fill_cmnds(char **arr, char *line, int i)
{
	int j;
	int k;
	int index;

	j = 0;
	k = -i;
	index = 0;
	while (line[j] && i >= 0)
	{
		if (k == 0 && !is_space(line[j]) && line[j] != '|')
		{
			arr[index] = malloc(sizeof(char) * count_chars(line + j) + 1);
			if (!arr[index])
				return (printf("malloc fail\n"), NULL);
			arr[index] = ft_memcpy(arr[index], line + j, (size_t)count_chars(line + j));
			j += count_chars(line + j);
			index++;
		}
		if (line[j] == '|')
		{
			i--;
			k++;
		}
		j++;
	}
	return (arr);
}


void print_THIS_SHIT(pipex_t *data)
{
	int i;
	int j;

	i = 0;
	while (data->cmnds[i])
	{
		j = 0;
		while (data->cmnds[i][j])
			printf("THIS: %sSHESH\n", data->cmnds[i][j++]);
		i++;
	}
}

void init(pipex_t *data, char *line)
{
	int i;
	int count;

	i = 0;
	count = count_cmnds(line);
	data->cmnds = malloc(sizeof(char **) * count + 1);
	if (!data->cmnds)
		return (printf("malloc fail!\n"), error_code());
	data->cmnds[count] = 0;
	data->paths = malloc(sizeof(char *) * count + 1);
	if (!data->paths)
		return (printf("malloc fail!\n"), error_code());
	data->paths[count] = 0;
	printf("PENIS\n");
	while (i < count)
	{
		printf("COUNT: %d\n", count_elem(line, i));
		data->cmnds[i] = malloc(sizeof(char *) * count_elem(line, i) + 1);
		if (!data->cmnds[i])
			return (printf("malloc fail!\n"), error_code());
		data->cmnds[i][count_elem(line, i)] = 0;
		data->cmnds[i] = fill_cmnds(data->cmnds[i], line, i);
		i++;
	}
}

void pipex(char *line, char **env)
{
	pipex_t *data;

	data = malloc(sizeof(pipex_t) * 1);
	if (!data)
		return (write(1, "malloc fail", 11), error_code());
	init(data, line);
	print_THIS_SHIT(data);
	if (env)
		;
	free_struct(data);
	free(line);
}
