# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 17:01:03 by asohrabi          #+#    #+#              #
#    Updated: 2024/01/30 10:54:09 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG = pipex

FUNC = pipex.c \
			pipex_utils.c \

FUNC_BONUS = pipex_bonus.c \
				pipex_utils_bonus.c \
				here_doc_bonus.c \

OBJ = ${FUNC:.c=.o}

OBJ_BONUS = ${FUNC_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all: ${PROG}

${PROG}: ${OBJ} .mandatory
	@rm -rf ${OBJ_BONUS}
	@make re -C ./libft
	@cc ${OBJ} -Llibft -lft -o ${PROG}

.mandatory: 
	@rm -rf .bonus
	@touch .mandatory

%.o: %.c
	cc ${CFLAGS} -c $< -o $@

bonus: .bonus

.bonus: ${OBJ_BONUS}
	@rm -rf ${OBJ}
	@make re -C ./libft
	@cc ${OBJ_BONUS} -Llibft -lft -o ${PROG}
	@rm -rf .mandatory
	@touch .bonus

clean:
	@make clean -C ./libft
	@rm -rf .mandatory
	@rm -rf .bonus
	rm -rf ${OBJ} ${OBJ_BONUS}

fclean: clean
	@make fclean -C ./libft
	@rm -rf ${NAME}
	rm -rf ${PROG}

re: fclean all

re_bonus: fclean bonus

.PHONY: all, clean, fclean, re, bonus, re_bonus
