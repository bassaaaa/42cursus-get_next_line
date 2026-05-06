/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsito <tsito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 22:26:16 by tsito             #+#    #+#             */
/*   Updated: 2026/05/06 22:49:55 by tsito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*resize_buf_if_needed(char *buf, size_t *size, size_t i)
{
	char	*resized;
	size_t	j;

	if (i + 1 >= *size)
	{
		*size += BUFFER_SIZE;
		resized = malloc(*size);
		if (!resized)
		{
			free(buf);
			return (NULL);
		}
		j = 0;
		while (j + BUFFER_SIZE < *size)
		{
			resized[j] = buf[j];
			j++;
		}
		free(buf);
		return (resized);
	}
	return (buf);
}

char	*gnl_read_line(int fd, char *buf, size_t size)
{
	size_t	i;
	int		bytes;

	i = 0;
	while (1)
	{
		buf = resize_buf_if_needed(buf, &size, i);
		if (!buf)
			return (NULL);
		bytes = read(fd, &buf[i], 1);
		if (bytes <= 0)
			break ;
		i++;
		if (buf[i - 1] == '\n')
			break ;
	}
	if (bytes < 0 || i == 0)
	{
		free(buf);
		return (NULL);
	}
	buf[i] = '\0';
	return (buf);
}
