#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(void)
{
	char *s;

	int i;
	i = -1;
	s = malloc(i);
	if (!s)
		return (perror("malloc failed!"), exit(errno), 1);
	return (0);
}
