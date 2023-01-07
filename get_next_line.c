/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/07 09:30:38 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
	i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (out);
}


char	*transfer(char *out, int i)
{
	char	*newout;
	int		c;

	c = 0;

	newout = malloc(50 * sizeof(char));
	while (out[i] != '\n' )
	{
		newout[c] = out[i];
		i++;
		c++;
	}
	newout[c] = out[i];
	return (newout);
}

int	checknl(char *out)
{
	int	i;

	i = 0;
	while (out[i] != '\n' && out[i] != '\0')
	{
		i++;
	}
	if (out[i] == '\n')
		return (1);
	else
		return (0);
}

char	*get_next_line(int fd)
{
	char		*whole;
	char		*temp;
	static int	i;

	temp = malloc(BUFFER_SIZE * sizeof(char));
	if (i == 0)
	{
		whole = malloc(BUFFER_SIZE + 1 * sizeof(char));
		whole[BUFFER_SIZE] = '\0';
		read(fd, whole, BUFFER_SIZE);
	}
	if (i != 0 && checknl(whole) == 0)
	read(fd, temp, BUFFER_SIZE);
	whole = ft_strjoin(whole, temp);
	free(temp);
	return (transfer(whole, i));
}

int	main(void)
{
	int		fd_to_read;
	char	*out;

	fd_to_read = open("Testtext.txt", O_RDONLY);
	out = get_next_line(fd_to_read);
	printf("%s", out);
	printf("%s", get_next_line(fd_to_read));
	printf("%s", get_next_line(fd_to_read));
	printf("%s", get_next_line(fd_to_read));
}
