# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 17:01:03 by asohrabi          #+#    #+#              #
#    Updated: 2023/12/15 20:48:55 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG = pipex

FUNC = pipex.c \
			pipex_utils.c \

OBJ = ${FUNC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	cc ${CFLAGS} -c $< -o $@

all: ${PROG}

${PROG}: ${OBJ}
	@make re -C ./libft
	@cc ${OBJ} -Llibft -lft -o ${PROG}

clean:
	@make clean -C ./libft
	rm -f ${OBJ}

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	rm -f ${PROG}

re: fclean all

.PHONY: all, clean, fclean, re