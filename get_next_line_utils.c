/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:24:17 by pramos-m          #+#    #+#             */
/*   Updated: 2022/11/16 16:17:53 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_buffer(char *storage, char *buff)
{
	char	*str;

	if (!storage)
	{
		storage = malloc(sizeof(char) * 1);
		if (!storage)
			return (NULL);
		storage[0] = '\0';
	}
	str = malloc(sizeof(char) * ft_strlen(storage) + ft_strlen(buff) + 1);
	if (!str)
		return (ft_free(&storage));
	str = ft_strjoin_copy(str, storage, buff);
	ft_free(&storage);
	return (str);
}

char	*ft_strjoin_copy(char *str, char *storage, char *buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (storage[i] != '\0')
	{
		str[i] = storage[i];
		i++;
	}
	while (buff[j])
	{
		str[i + j] = buff[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
