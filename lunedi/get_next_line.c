/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarrara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:20:22 by mcarrara          #+#    #+#             */
/*   Updated: 2025/11/10 17:43:55 by mcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *print_new_line(char *storage, char *ptr_static) 
{
	char	*line;
	size_t	len;
 
	len = ptr_static - storage;
	line = (char *)malloc(sizeof(char) * len + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, storage, len + 1);	
	return (line);
}

char	*fix_storage(char *storage, char *ptr_static)
{
	char	*new_storage;

	new_storage = ft_strdup(ptr_static + 1);
	if (new_storage == 0)
		return (NULL);
	free(storage);
	return (new_storage);
}

char	*get_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	static char	*storage = NULL;
	static size_t	bytes = 1;
	char	*new_line;
	static int	first_call = 0;
	static char	*ptr_static;

	if (first_call++ == 0)
		storage = ft_strdup("");
	while (bytes > 0)
	{
		if (!ft_strchr(storage, '\n'))
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			buffer[bytes] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
		else
		{
			ptr_static = ft_strchr(storage, '\n');
			new_line = print_new_line(storage, ptr_static);
			storage = fix_storage(storage, ptr_static);
			return (new_line);
		}
	}
	while (bytes == 0)
	{
			new_line = print_new_line(storage, ptr_static);
			free(storage);
			return (new_line);
	}
	return (NULL);
}

char *get_next_line(int fd)
{
	char 	*line;

	line = get_line(fd);
	return (line);
}
