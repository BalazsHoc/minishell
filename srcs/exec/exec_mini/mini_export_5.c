#include "../../../minishell.h"

void	set_rest(t_pipex *data, char **buf)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (data->cur_env[++j])
	{
		if (!buf[i])
			buf[i] = data->cur_env[j];
		else
			j--;
		i++;
	}
}
