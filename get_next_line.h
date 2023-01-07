/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:43:40 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/07 13:36:44 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
// int		ft_strlen(const char *str);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*transfer(char *out, int *pi, int transfersize, int readnull);
// int		checknl(char *out, int i, int *ptransfersize);

#endif
