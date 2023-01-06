/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:47:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/06 10:45:18 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	findnewline(int fd)
{
	int		c;

	c = 0;
	while (fd + c != '\n')
	{
		c++;
	}
	return (c);
}

char	*get_next_line(int fd)
{
	char	*out;

	out = calloc(50, sizeof(char));

	read(fd, out, findnewline(fd));

	return (out);
}

int	main(void)
{
	int	fd_to_read;

	fd_to_read = open("Testtext.txt", O_RDONLY);
	printf("%s", get_next_line(fd_to_read));
}
