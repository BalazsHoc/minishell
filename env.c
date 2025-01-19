// #include "minishell.h"

// char    **new_env(char **env)
// {
//     char    **new;
//     int i;
	
// 	i = -1;
// 	new = ft_calloc(sizeof(char *), (count_env(env) + 1));
// 	while (++i < count_env(env))
// 	{
// 		new[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
// 		if (!new[i])
// 			return (printf("malloc fail!\n"), NULL);
// 		ft_memcpy(new[i], env[i], ft_strlen(env[i]));
// 		new[i][ft_strlen(env[i])] = 0;
// 	}
//     return (new);
// }
