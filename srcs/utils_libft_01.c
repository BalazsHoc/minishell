#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*ft_strdup(t_pipex *data, const char *s)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	while (s[j] != '\0')
		j++;
	ptr = ft_calloc(sizeof(char), (j + 1));
	if (!ptr)
		return (perror("malloc failed!"), error_code(data), NULL);
	ptr[j] = 0;
	while (i < j)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		count++;
		if (!str[i + 1])
			break;
		i++;
	}
	return (count);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	end;
	int		i;

	if (!s1 || !*s1 || !set || !*set)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	end = ft_strlen(s1);
	while (end != 0 && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, i, end + 1));
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}