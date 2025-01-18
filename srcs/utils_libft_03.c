#include "../minishell.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (nptr[0] == '\0')
		return (0);
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] == '0')
		i++;
	if (ft_strlen(nptr + i) >= 11)
		return ((long)INT_MAX + 1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (!nmemb || !size)
		return (malloc(0));
	if (size > SIZE_MAX / nmemb)
		return (0);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (0);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}


size_t	ft_digit_count(long int n)
{
	size_t	digits;

	if (n < 0)
	{
		digits = 1;
		n *= -1;
	}
	else
		digits = 0;
	if (n == 0)
		digits = 1;
	while (n > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		digits;
	long int	num;

	num = n;
	digits = ft_digit_count(num);
	if (n < 0)
		num *= -1;
	result = malloc(sizeof(char) * (digits + 1));
	if (!result)
		return (NULL);
	*(result + digits) = '\0';
	while (digits--)
	{
		*(result + digits) = (num % 10) + 48;
		num = num / 10;
	}
	if (n < 0)
		*(result + 0) = '-';
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest != src)
	{
		while (i < n)
		{
			// if (((unsigned char *)src)[i] == '\n')
			// 	break ;
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}