/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarrara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:16:51 by mcarrara          #+#    #+#             */
/*   Updated: 2025/11/10 17:25:58 by mcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# elif (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*get_line(int fd);
char	*print_new_line(char *storage, char *ptr_static);
char	*fix_storage(char *storage, char *ptr_static);
char	*ft_strdup(const char *s);
char	*ft_strchr(char const *s, int c);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
