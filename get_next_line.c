/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/07 14:40:49 by fvon-nag         ###   ########.fr       */
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

char	*transfer(char *out, int *pi, int transfersize)
{
	char	*newout;
	int		c;
	int		*i;

	if (transfersize == 0)
		transfersize = ft_strlen(out);

	i = pi;
	c = 0;
	newout = malloc(transfersize * sizeof(char));
	while (c < transfersize)
	{
		newout[c] = out[*i];
		(*i)++;
		c++;
	}

	return (newout);
}

int	checknl(char *out, int i, int *ptransfersize)
{
	while (out[i] != '\n' && out[i] != '\0')
	{
		i++;
	}
	if (out[i] == '\n')
	{
		*ptransfersize = i + 1;
		return (1);
	}
	if (out[i] != '\n' && i == 0)
		return (-1);
	else
		return (0);
}

char	*get_next_line(int fd)
{
	char			*whole;
	char			temp[BUFFER_SIZE + 1];
	static int		i;
	int				transfersize;
	int				readstat;

	whole = malloc(BUFFER_SIZE + 1 * sizeof(char));
	readstat =  read(fd, temp, BUFFER_SIZE);
	if (readstat <= 0)
	{
		free(whole);
		return (NULL);
	}
	else if (readstat < BUFFER_SIZE)
	{
		free(whole);
		temp[BUFFER_SIZE] = '\0';
		checknl(temp, i, &transfersize);
		return (transfer(temp, &i, transfersize));
	}
	else
	{
	whole = ft_strjoin(whole, temp);
		while (checknl(whole, i, &transfersize) == 0)
		{
			readstat = read(fd, temp, BUFFER_SIZE);
			if (readstat < BUFFER_SIZE && readstat != 0)
			{
				whole = ft_strjoin(whole, temp);
				break ;
			}
			else if (readstat == 0)
				break ;
			whole = ft_strjoin(whole, temp);
		}
		return (transfer(whole, &i, transfersize));
	}
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
// }
