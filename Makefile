# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 09:38:36 by fvon-nag          #+#    #+#              #
#    Updated: 2023/01/06 09:52:35 by fvon-nag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = get_next_line

SOURCES := get_next_line.c\
		get_next_line_utils.c



OBJECTS = $(SOURCES:.c=.o)

CFLAGS += -Wall -Wextra -Werror -D BUFFER_SIZE=42

$(NAME) : ${OBJECTS}
	$(CC) $(CFLAGS) -o ${NAME} ${OBJECTS}

all: ${NAME}

clean :
	rm -f $(OBJECTS) $(BOBJECTS)
fclean : clean
	rm -f $(NAME)
re : fclean all

