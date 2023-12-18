# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 17:01:03 by asohrabi          #+#    #+#              #
#    Updated: 2023/12/18 18:10:03 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG = pipex

FUNC = pipex.c \
			pipex_utils.c \

FUNC_BONUS = pipex_bonus.c \
				pipex_utils_bonus.c \

OBJ = ${FUNC:.c=.o}

OBJ_BONUS = ${FUNC_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	cc ${CFLAGS} -c $< -o $@

all: ${PROG}

${PROG}: ${OBJ}
	@make re -C ./libft
	@cc ${OBJ} -Llibft -lft -o ${PROG}

bonus: .bonus

.bonus: ${OBJ_BONUS}
	@make re -C ./libft
	@cc ${OBJ_BONUS} -Llibft -lft -o ${PROG}
	@touch .bonus

clean:
	@make clean -C ./libft
	rm -f ${OBJ} ${OBJ_BONUS}

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	rm -f ${PROG}

re: fclean all

.PHONY: all, clean, fclean, re, bonus