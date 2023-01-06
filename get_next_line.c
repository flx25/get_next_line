/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/06 14:46:37 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*findnewline(char *out, int i)
{
	char	*newout;
	int 	c;

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
	char		*out;
	static int	i;

	out = calloc(50, sizeof(char));
	if (checknl(out) == 0)
		read(fd, out, BUFFER_SIZE);
	return (findnewline(out, i));
}

int	main(void)
{

	int	fd_to_read;
	char	*out;

	fd_to_read = open("Testtext.txt", O_RDONLY);
	out = get_next_line(fd_to_read);
	printf("%s", out);
	printf("%s", get_next_line(fd_to_read));
	printf("%s", get_next_line(fd_to_read));
	printf("%s", get_next_line(fd_to_read));
}
