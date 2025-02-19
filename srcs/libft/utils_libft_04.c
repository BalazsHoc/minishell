/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_04.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:49:45 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:49:47 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_det(char c, char det)
{
	if (c == det)
		return (1);
	return (0);
}

static int	ft_count_words(const char *s1, char det)
{
	int		words;
	size_t	i;

	words = 0;
	i = 0;
	while (s1[i])
	{
		if (i == 0 && !is_det(s1[i], det))
			words++;
		if (i > 0 && !is_det(s1[i], det) && is_det(s1[i - 1], det))
			words++;
		i++;
	}
	return (words);
}

static char	**ft_malloc_cpy(char **new, const char *s, char det, int wordcount)
{
	int		count;
	int		i;
	size_t	j;

	count = 0;
	i = -1;
	while (count < wordcount && ++i != INT_MIN)
	{
		if ((i == 0 && !is_det(s[i], det))
			|| (!is_det(s[i], det) && is_det(s[i - 1], det)))
		{
			j = 0;
			while (s[i + j] && !is_det(s[i + j], det))
				j++;
			new[count] = malloc(sizeof(char) * (j + 1));
			if (!new[count])
				return (NULL);
			new[count++][j] = '\0';
			j = 0;
			while (s[i] && !is_det(s[i], det))
				new[count - 1][j++] = s[i++];
		}
	}
	return (new);
}

static void	ft_merror(char **new)
{
	size_t	i;

	i = 0;
	while (new[i])
	{
		free_str(&new[i]);
		new[i] = NULL;
		i++;
	}
	free(new);
	new = NULL;
}

char	**ft_split(const char *s1, char c)
{
	char	**new;
	int		wordcount;

	wordcount = ft_count_words(s1, c);
	if (!wordcount)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	new = malloc(sizeof(char *) * (wordcount + 1));
	if (!new)
		return (NULL);
	if (ft_malloc_cpy(new, s1, c, wordcount))
		new[wordcount] = NULL;
	else
	{
		ft_merror(new);
		return (NULL);
	}
	return (new);
}
