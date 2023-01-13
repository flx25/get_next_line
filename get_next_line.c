/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/11 16:03:35 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ps;
	unsigned char	*pd;

	if (src == NULL && n != 0 && dest == 0)
		return (NULL);
	ps = (unsigned char *) src;
	pd = dest;
	while (n--)
	{
		*pd++ = (unsigned char) *ps++;
	}
	return (dest);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0x0);
	while (str[i] != '\0')
	{
	i++;
	}
	return (i);
}

char	*ft_strchr(char *c, int i)
{
	int	j;

	j = 0;
	if (!c)
		return (NULL);
	if (i == '\0')
		return ((char *)&c[ft_strlen(c)]);
	while (c[j] != '\0')
	{
		if (c[j] == (char) i)
			return ((char *)&c[j]);
		j++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0'
		&& s1[i] == s2[i])
	{
	i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*csrc;
	char	*cdest;

	if (src == NULL && n != 0 && dest == 0)
		return (NULL);
	csrc = (char *) src;
	cdest = (char *) dest;
	i = 0;
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
		return (dest);
	}
		i = n - 1;
	while (i >= 0)
	{
			cdest[i] = csrc[i];
			i--;
	}
	return (dest);
}

char	*ft_realloc(char *str, int size)
{
	char	*out;

	out = malloc(size * sizeof(char));
	if (str != NULL)
	{
		ft_memmove(out, str, ft_strlen(str));
		free(str);
	}
	out[ft_strlen(str)] = '\0';
	return (out);
}

char	*ft_readandsearch(int fd, char *buffer, char *line)
{
	int	readstat;

	readstat = 1;
	if (ft_strlen(buffer) == NULL) //maybe edit
		readstat = read(fd, buffer, BUFFER_SIZE);

	while (!ft_strchr(buffer, '\n') && readstat != 0)
	{
		line = ft_realloc(line, strlen(line + BUFFER_SIZE + 1));
		ft_memmove(line + strlen(line), buffer, strlen(buffer));
	}
		if(ft_strchr(buffer, '\n'))
		{
			memmove(line + ft_strlen(line), buffer, (size_t) (ft_strchr(buffer, '\n') - buffer));
		}
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_readandsearch(fd, buffer, &line);
}

int	main(void)
{
	int		fd_to_read;
	char	*out;

	fd_to_read = open("testtext.txt", O_RDONLY);
	out = get_next_line(fd_to_read);
	printf("%s", out);
	printf("%s", get_next_line(fd_to_read));
	printf("%s", get_next_line(fd_to_read));
	printf("%s", get_next_line(fd_to_read));
	close(fd_to_read);
}
