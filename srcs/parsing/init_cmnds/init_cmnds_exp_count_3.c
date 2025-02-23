#include "../../../minishell.h"

void	ft_strncpy_4(char **buf, char *elem, int size)
{
	int		i;
	char	*cur;

	i = -1;
	cur = *buf;
	while (++i < size)
	{
		if (elem[i] != ' ')
			cur[i] = elem[i];
		else
			cur[i] = '\n';
	}
}
