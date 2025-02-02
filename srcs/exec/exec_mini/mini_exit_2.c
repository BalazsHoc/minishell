#include "../../../minishell.h"

int	only_dec(char *str)
{
	int	i;
	int	check;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	check = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i] && check < i)
		return (1);
	return (0);
}

int	is_overflow_continue(char *str, int sign)
{
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result > 100000000000000000 && str[i + 1])
			|| (result > 922337203685477590)
			|| (result == 922337203685477580 && (str[i] == '8'
					|| str[i] == '9') && sign == 1)
			|| (result == 922337203685477580 && str[i] == '9' && sign == -1))
			return (1);
		result = result * (unsigned long long)10
			+ (unsigned long long)(str[i] - '0');
		i++;
	}
	return (0);
}

int	is_overflow(t_pipex *data, int index_1, int index_2)
{
	int		i;
	int		sign;
	char	*nptr;

	i = 0;
	sign = 1;
	nptr = data->l[index_1]->ops[index_2][1];
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
	if (ft_strlen(nptr + i) > 19)
		return (1);
	return (is_overflow_continue(nptr + i, sign));
}
