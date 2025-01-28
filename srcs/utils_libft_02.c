#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2 || !*s1 || !*s2)
		return (-1);
	// printf("S1: %s$ | S2: %s$ %ld\n", s1, s2, n);
	while (i < n)
	{
		if (!s1[i])
		{
			if (s2[i])
				return (-1);
		}
		else if (!s2[i])
			return (-1);
		// printf("I: %s$ | N: %ld$\n", s1 + i, n);
		else if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	// return (printf("THE SAME\n"), 0);
	return (0);
}

int ft_strcmp_2(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1 && s2 && (s1[i] == s2[i]))
	{
		if (s1[i] == 0 && s2[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len, t_pipex *data)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!(s))
		return (0);
	if ((start >= ft_strlen(s)) || (len == 0))
		return (free_str(&s), ft_calloc(1, sizeof(char), data));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub = ft_calloc(sizeof(char), (len + 1), data);
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	return (free_str(&s), sub);
}

char	*ft_strjoin(char const *s1, char const *s2, t_pipex *data)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (s1 == 0 && s2 == 0)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	joined = ft_calloc(sizeof(char), (i + 1), data);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}