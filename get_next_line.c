/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/11 14:41:53 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*out;
	int		i;
	int		j;

	out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
	out[j] = s1[i];
	i++;
	j++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
	out[j] = s2[i];
	i++;
	j++;
	}
	out[j] = '\0';
	free(s1);
	return (out);
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

char	*ft_read(int fd, char *str)
{
	int		i;
	char	temp[BUFFER_SIZE + 1];

	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		temp[i] = '\0';
		str = ft_strjoin(str, temp);
	}
	return (str);
}

char	*ft_getline(char *str)
{
	int		i;
	char	*out;

	i = 0;
	if (!str[i])
		return (NULL);

	while (str[i] && str[i] != '\n')
		i++;
	out = malloc((i + 2) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		out[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_getrest(char *str)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	out = malloc(((ft_strlen(str) - i) + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i++;
	while (str[i])
	{
		out[j] = str[i];
		j++;
		i++;
	}
	out[j] = '\0';
	free(str);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	str = ft_read(fd, str);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	line = ft_getline(str);
	str = ft_getrest(str);
	return (line);
}

// int	main(void)
// {
// 	int		fd_to_read;
// 	char	*out;

// 	fd_to_read = open("Testtext.txt", O_RDONLY);
// 	out = get_next_line(fd_to_read);
// 	printf("%s", out);
// 	printf("%s", get_next_line(fd_to_read));
// 	printf("%s", get_next_line(fd_to_read));
// 	printf("%s", get_next_line(fd_to_read));
// 	close(fd_to_read);
// }
