/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:14:46 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/08 13:14:51 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*gnl_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	i;
	size_t	len;

	i = 0;
	len = nmemb * size + 1;
	if (!nmemb || !size)
		return (NULL);
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	buffer = (void *)malloc(len);
	if (!buffer)
		return (NULL);
	while (i < len)
	{
		((char *)buffer)[i] = '\0';
		i++;
	}
	return (buffer);
}

char	*gnl_join_free(char *static_buf, char *buffer)
{
	char	*joined;

	joined = gnl_join_buffer(static_buf, buffer);
	if (!joined)
		return (gnl_free(&static_buf), NULL);
	gnl_free(&static_buf);
	gnl_free(&buffer);
	return (joined);
}

char	*gnl_join_buffer(char *line, char *buffer)
{
	char	*joined;
	int		i;
	int		j;

	if (!line || !buffer)
		return (NULL);
	joined = (char *)gnl_calloc((gnl_strlen(line)
				+ gnl_strlen(buffer) + 1), sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (line && line[i] != '\0')
	{
		joined[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j] != '\0')
	{
		joined[i + j] = buffer[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*reading(int fd, char *static_buf)
{
	char	*buffer;
	ssize_t	return_of_read;

	if (!static_buf)
		static_buf = gnl_calloc(1, 1);
	if (!static_buf)
		return (NULL);
	return_of_read = 1;
	while (!gnl_newline(static_buf) && return_of_read > 0)
	{
		buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (gnl_free(&static_buf), NULL);
		return_of_read = read(fd, buffer, BUFFER_SIZE);
		if (return_of_read == -1)
			return (gnl_free(&buffer), gnl_free(&static_buf), NULL);
		buffer[return_of_read] = '\0';
		static_buf = gnl_join_free(static_buf, buffer);
		if (!static_buf)
			return (gnl_free(&buffer), NULL);
		if (return_of_read < BUFFER_SIZE)
			break ;
	}
	return (static_buf);
}

char	*get_next_line(int fd, bool flag)
{
	static char	*buf;
	char		*output;

	if (fd < 0 || BUFFER_SIZE < 1 || flag == 1)
		return (gnl_free(&buf), NULL);
	buf = reading(fd, buf);
	if (!buf)
		return (NULL);
	output = gnl_strcpy(buf);
	if (!output)
		return (gnl_free(&buf), NULL);
	if (gnl_newline(buf) == 1)
	{
		buf = gnl_fromnl(buf);
		return (output);
	}
	return (gnl_free(&buf), free(output), NULL);
}
// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line = get_next_line(fd, 0);

// 	printf("line: x%sx", line);
// 	while (line != NULL)
// 	{
// 		printf("line: x%sx", line);
// 		free(line);
// 		line = get_next_line(fd, 0);
// 		printf("line: x%sx", line);
// 		free(line);
// 		line = get_next_line(fd, 0);
// 		printf("line: x%sx", line);
// 		// get_next_line(fd, 1);
// 	}
// 	free(line);
// 	close(fd);
// 	return 0;
// }
