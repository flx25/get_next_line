/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/14 14:17:56 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*out;

	if ((nmemb >= __SIZE_MAX__ && size >= __SIZE_MAX__))
		return (NULL);
	out = (unsigned char *) malloc(nmemb * size);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		out[i] = 0;
		i++;
	}
	return (out);
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

int	ft_strchridx(char *c, int i)
{
	size_t	j;

	j = 0;
	if (!c)
		return (-1);
	if (i == '\0')
		return (ft_strlen(c));
	while (c[j] != '\0')
	{
		if (c[j] == (char) i)
			return (j);
		j++;
	}
	return (-1);
}

char	*ft_strjoin(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*nstr;

	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (!str || !buff)
		return (NULL);
	nstr = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
	if (nstr == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (str)
		while (str[++i] != '\0')
			nstr[i] = str[i];
	while (buff[j] != '\0')
		nstr[i++] = buff[j++];
	nstr[ft_strlen(str) + ft_strlen(buff)] = '\0';
	free(str);
	return (nstr);
}

char	*readtostr(int fd, char *str)
{
	char	*buff;
	int		readstat;

	readstat = 1;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);

	while (!ft_strchr(str, '\n') && readstat != 0)
	{
		readstat = read(fd, buff, BUFFER_SIZE);
		if (readstat == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readstat] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_getline(char *str)
{
	int		i;
	char	*nstr;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	nstr = malloc((i + 2) * sizeof(char));
	if (!nstr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		nstr[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

char	*getnewstr(char *str)
{
	int		i;
	int		j;
	char	*nstr;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	nstr = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		nstr[j++] = str[i++];
	nstr[j] = '\0';
	free(str);
	return (nstr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	str = readtostr(fd, str);
	if (!str)
		return (NULL);
	line = ft_getline(str);
	str = getnewstr(str);
	return (line);
}

// int	main(void)
// {
// 	int		fd_to_read;
// 	char	*out;

// 	fd_to_read = open("41_with_nl", O_RDONLY);
// 	printf("%s", get_next_line(fd_to_read));
// 	close(fd_to_read);
// }
