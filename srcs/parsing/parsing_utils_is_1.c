#include "../../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int is_quote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

int is_quote_one(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int is_quote_two(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int is_or(char *cur)
{
	if (cur[0] == '|' && cur[-1] == '|')
		return (1);
	if (cur[0] == '|' && cur[+1] == '|')
		return (1);
	return (0);
}