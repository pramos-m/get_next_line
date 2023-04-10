/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:24:26 by pramos-m          #+#    #+#             */
/*   Updated: 2022/11/16 16:31:26 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!storage[fd] || (storage[fd] && !ft_strchr(storage[fd], '\n')))
		storage[fd] = fill_storage(storage[fd], fd);
	if (!storage[fd])
		return (NULL);
	line = take_line(storage[fd]);
	if (!line)
		return (ft_free(&storage[fd]));
	storage[fd] = clean_storage(storage[fd]);
	return (line);
}

char	*fill_storage(char *storage, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		rd_bytes;

	rd_bytes = 1;
	buffer[0] = '\0';
	while (rd_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);
		if (rd_bytes > 0)
		{
			buffer[rd_bytes] = '\0';
			storage = ft_strjoin_buffer(storage, buffer);
		}
	}
	if (rd_bytes == -1)
		return (ft_free(&storage));
	return (storage);
}

char	*take_line(char	*storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage || storage[0] == '\0')
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1 + (storage[i] == '\n'));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_storage(char *storage)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
		return (ft_free(&storage));
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(storage) - i));
	if (!tmp)
		return (ft_free(&storage));
	i++;
	j = 0;
	while (storage[i + j])
	{
		tmp[j] = storage[i + j];
		j++;
	}
	tmp[j] = '\0';
	ft_free(&storage);
	return (tmp);
}

void	*ft_free(char **storage)
{
	free(*storage);
	*storage = NULL;
	return (NULL);
}
