/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsito <tsito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:52:39 by tsito             #+#    #+#             */
/*   Updated: 2026/05/03 14:49:16 by tsito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
    line = read_line(fd);
	return (line);
}
//
// #include <fcntl.h>
// #include <stdio.h>
//
// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*buf;
//
// 	fd1 = open("./empty", O_RDONLY);
// 	fd2 = open("./test2", O_RDONLY);
// 	buf = get_next_line(fd1);
// 	printf("%s", buf);
// 	buf = get_next_line(fd2);
// 	printf("%s", buf);
// 	buf = get_next_line(fd1);
// 	printf("%s", buf);
// 	buf = get_next_line(fd2);
// 	printf("%s", buf);
// 	close(fd1);
// 	close(fd2);
// 	free(buf);
// }
