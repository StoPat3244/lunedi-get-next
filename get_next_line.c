/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarrara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:20:22 by mcarrara          #+#    #+#             */
/*   Updated: 2025/11/11 18:06:58 by mcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *print_new_line(char *storage, char *ptr) 
{
	char	*line;
	size_t	len;
	char	*temporal;
	
	if (!ptr)
	{
		temporal = storage;
		line = ft_strdup(storage);
		if (!line)
			return (NULL);
		free(temporal);
		storage = NULL;
		return (line);
	}
	len = ptr - storage;
	line = (char *)malloc(sizeof(char) * len + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, storage, len + 1);
	return (line);
}

char	*build_storage(char *storage, char *buffer, char *ptr, size_t bytes)
{
	char	*temporal;
	char	*new_storage;
	
	temporal = storage;
	if (!ptr)
	{
		buffer[bytes] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (storage == 0)
			return (NULL);
		free(temporal);
		temporal = NULL;
		return (storage);
	}
	else
	{
		new_storage = ft_strdup(ptr + 1);
		if (new_storage == 0)
			return (NULL);		
	}
	return (new_storage);
}

char *get_next_line(int fd)
{
	char 	*line;
	char	buffer[BUFFER_SIZE + 1];
	static char	*storage;
	static size_t	bytes = 1;
	char	*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (bytes == 0)
		return (NULL);
	ptr = ft_strchr(storage, '\n');
	while (!ptr)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
		{
			line = print_new_line(storage, ptr);	
			return (line);
		}
		storage = build_storage(storage, buffer, ptr, bytes);
		ptr = ft_strchr(storage, '\n');
	}
	line = print_new_line(storage, ptr);
	storage = build_storage(storage, buffer, ptr, bytes);
	return (line);
}
