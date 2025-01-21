// int	ft_atoi(const char *nptr)
// {
// 	int		i;
// 	int		sign;
// 	long	result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	if (nptr[0] == '\0')
// 		return (0);
// 	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
// 		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
// 		i++;
// 	if (nptr[i] == '-' || nptr[i] == '+')
// 	{
// 		if (nptr[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		result = result * 10 + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (sign * result);
// }

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*buffer;

// 	if (!nmemb || !size)
// 		return (malloc(0));
// 	if (size > SIZE_MAX / nmemb)
// 		return (0);
// 	buffer = (void *)malloc(size * nmemb);
// 	if (!buffer)
// 		return (0);
// 	ft_bzero(buffer, size * nmemb);
// 	return (buffer);
// }


// static size_t	ft_digit_count(long int n)
// {
// 	size_t	digits;

// 	if (n < 0)
// 	{
// 		digits = 1;
// 		n *= -1;
// 	}
// 	else
// 		digits = 0;
// 	if (n == 0)
// 		digits = 1;
// 	while (n > 0)
// 	{
// 		n = n / 10;
// 		digits++;
// 	}
// 	return (digits);
// }

// char	*ft_itoa(int n, t_pipex *data)
// {
// 	char		*result;
// 	size_t		digits;
// 	long int	num;

// 	num = n;
// 	digits = ft_digit_count(num);
// 	if (n < 0)
// 		num *= -1;
// 	result = ft_calloc(sizeof(char), (digits + 1), data);
// 	while (digits--)
// 	{
// 		*(result + digits) = (num % 10) + 48;
// 		num = num / 10;
// 	}
// 	if (n < 0)
// 		*(result + 0) = '-';
// 	return (result);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dest != src)
// 	{
// 		while (i < n)
// 		{
// 			// if (((unsigned char *)src)[i] == '\n')
// 			// 	break ;
// 			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
// 			i++;
// 		}
// 	}
// 	return (dest);
// }



// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	if (!s1 || !s2 || !*s1 || !*s2)
// 		return (-1);
// 	// printf("S1: %s$ | S2: %s$ %ld\n", s1, s2, n);
// 	while (i < n)
// 	{
// 		if (!s1[i])
// 		{
// 			if (s2[i])
// 				return (-1);
// 		}
// 		else if (!s2[i])
// 			return (-1);
// 		// printf("I: %s$ | N: %ld$\n", s1 + i, n);
// 		else if (s1[i] != s2[i])
// 			return (s1[i] - s2[i]);
// 		i++;
// 	}
// 	// return (printf("THE SAME\n"), 0);
// 	return (0);
// }

// int ft_strcmp_2(char *s1, char *s2)
// {
// 	int i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	while (s1 && s2 && (s1[i] == s2[i]))
// 	{
// 		if (s1[i] == 0 && s2[i] == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	unsigned int	i;
// 	char			*sub;

// 	i = 0;
// 	if (!(s))
// 		return (0);
// 	if ((start >= ft_strlen(s)) || (len == 0))
// 		return (free_str(&s), ft_calloc(1, sizeof(char)));
// 	if (len > (ft_strlen(s) - start))
// 		len = ft_strlen(s) - start;
// 	sub = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!sub)
// 		return (free_str(&s), NULL);
// 	while (i < len)
// 	{
// 		sub[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	sub[i] = '\0';
// 	return (free_str(&s), sub);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*joined;
// 	size_t	i;
// 	size_t	j;

// 	if (s1 == 0 && s2 == 0)
// 		return (0);
// 	i = ft_strlen(s1) + ft_strlen(s2);
// 	joined = ft_calloc(sizeof(char), (i + 1));
// 	if (!joined)
// 		return (0);
// 	joined[i] = 0;
// 	i = 0;
// 	while (s1[i])
// 	{
// 		joined[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		joined[i + j] = s2[j];
// 		j++;
// 	}
// 	return (joined);
// }