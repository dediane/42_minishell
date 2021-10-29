/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:50:43 by ddecourt          #+#    #+#             */
/*   Updated: 2021/06/29 21:52:41 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_line(char **tmp_buffer, char *buf, int size)
{
	char	*tmp;

	buf[size] = '\0';
	if (0 != *tmp_buffer)
	{
		tmp = ft_strjoin(*tmp_buffer, buf);
		free(*tmp_buffer);
	}
	else
		tmp = ft_strndup(buf, size);
	*tmp_buffer = tmp;
	if (ft_strchr(*tmp_buffer, '\n'))
		return (1);
	return (0);
}

static int	check(char **tmp_buffer, char **line)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_strchr(*tmp_buffer, '\n');
	if (ptr)
	{
		*line = ft_strndup(*tmp_buffer, ptr - *tmp_buffer);
		tmp = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		free(*tmp_buffer);
		*tmp_buffer = tmp;
		return (1);
	}
	else
	{
		*line = *tmp_buffer;
		*tmp_buffer = 0;
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	int			bytes_read;
	static char	*tmp_buffer[10240];
	char		*buf;

	if (fd < 0 || fd >= 10240 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(buf))
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read >= 0)
	{
		if (get_line(&tmp_buffer[fd], buf, bytes_read) || bytes_read <= 0)
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bytes_read < 0)
		return (-1);
	return (check(&tmp_buffer[fd], line));
}
