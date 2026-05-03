/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsito <tsito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 22:26:16 by tsito             #+#    #+#             */
/*   Updated: 2026/05/03 14:47:37 by tsito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*expand_line(char *line, size_t size)
{
	char	*newline;
	size_t	i;

	i = 0;
	newline = malloc(size);
	if (!newline)
	{
		free(line);
		return (NULL);
	}
	while (i < size - BUFFER_SIZE)
	{
		newline[i] = line[i];
		i++;
	}
	free(line);
	return (newline);
}

char	*read_line(int fd)
{
	size_t	size;
	size_t	i;
	char	*line;
	int		bytes;

	size = BUFFER_SIZE;
	line = malloc(size);
	if (!line)
		return (NULL);
	i = 0;
	while (1)
	{
		if (i + BUFFER_SIZE >= size) {
            size += BUFFER_SIZE;
			line = expand_line(line, size);
        }
		bytes = read(fd, &line[i], 1);
		if (bytes <= 0) {
            free(line);
			return NULL;
        }
		if (line[i++] == '\n')
			break ;
	}
	return (line);
}
