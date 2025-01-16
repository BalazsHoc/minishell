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

char	*reading(int fd, char *static_buf, t_pipex *data)
{
	char	*buffer;
	ssize_t	return_of_read;

	if (!static_buf)
		static_buf = gnl_calloc(1, 1);
	if (!static_buf)
		return (error_code(data), NULL);
	return_of_read = 1;
	while (!gnl_newline(static_buf) && return_of_read > 0)
	{
		buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (gnl_free(&static_buf), error_code(data), NULL);
		write(1, "> ", 2);
		return_of_read = read(fd, buffer, BUFFER_SIZE);
		if (return_of_read == -1)
			return (gnl_free(&buffer), gnl_free(&static_buf), NULL); // Ctrl C
		buffer[return_of_read] = '\0';
		static_buf = gnl_join_free(static_buf, buffer);
		if (!static_buf)
			return (gnl_free(&buffer), error_code(data), NULL);
		if (return_of_read < BUFFER_SIZE)
			break ;
	}
	return (static_buf);
}

char	*get_next_line(int fd, t_pipex *data)
{
	static char	*buf;
	char		*output;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (gnl_free(&buf), error_code(data), NULL);
	buf = reading(fd, buf, data);
	output = gnl_strcpy(buf, data);
	if (!output)
		return (gnl_free(&buf), NULL); // Ctrl D
	if (gnl_newline(buf) == 1)
	{
		buf = gnl_fromnl(buf);
		return (output);
	}
	return (gnl_free(&buf), free(output), NULL);
}
