/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsito <tsito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 22:26:16 by tsito             #+#    #+#             */
/*   Updated: 2026/05/09 19:22:46 by tsito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_to_resized(char *buf, size_t i, size_t new_size)
{
	char	*resized;
	size_t	j;

	resized = malloc(new_size);
	if (!resized)
	{
		free(buf);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		resized[j] = buf[j];
		j++;
	}
	free(buf);
	return (resized);
}

static char	*resize_buf_if_needed(char *buf, size_t *size, size_t i)
{
	char	*resized;
	size_t	new_size;

	if (i + 1 >= *size)
	{
		new_size = *size * 2;
		if (new_size <= *size)
		{
			free(buf);
			return (NULL);
		}
		resized = copy_to_resized(buf, i, new_size);
		if (!resized)
			return (NULL);
		*size = new_size;
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
