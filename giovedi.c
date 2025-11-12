/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarrara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:34:16 by mcarrara          #+#    #+#             */
/*   Updated: 2025/11/12 14:07:00 by mcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*print_new_line(char *storage, char *ptr)
{
	char	*line;
	size_t	len;

	if (!ptr)
	{
		line = ft_strdup(storage);
		free(storage);
		storage = NULL;
		if (!line)
			return (NULL);
		return (line);
	}
	len = ptr - storage;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	ft_strlcpy(line, storage, len + 2);
	return (line);
}

char	*fix_storage(char *storage, char *ptr)
{
	char	*new_storage;

	if (!ptr)
		return (NULL);
	ptr++;
	if (*ptr == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	new_storage = ft_strdup(ptr);
	free(storage);
	storage = NULL;
	return (new_storage);
}

char	*build_storage(char *storage, char *buffer, size_t bytes)
{
	char	*new_storage;

	buffer[bytes] = '\0';
	if (!storage)
		return (ft_strdup(buffer));
	new_storage = ft_strjoin(storage, buffer);
	if (!new_storage)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	free(storage);
	storage = NULL;
	return (new_storage);
}

char	*read_buffer(int fd, char *storage, char *buffer)
{
	ssize_t	bytes;
	char	*ptr;

	ptr = NULL;
	while (!ptr)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(storage);
			storage = NULL;
			return (NULL);
		}
		if (bytes == 0)
			break ;
		storage = build_storage(storage, buffer, bytes);
		if (!storage)
			return (NULL);
		ptr = ft_strchr(storage, '\n');
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*ptr;

	if (fd < 0)
		return (NULL);
	storage = read_buffer(fd, storage, buffer);
	if (!storage || *storage == '\0')
		return (NULL);
	ptr = ft_strchr(storage, '\n');
	line = print_new_line(storage, ptr);
	storage = fix_storage(storage, ptr);
	return (line);
}
