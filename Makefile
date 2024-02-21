# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 17:01:03 by asohrabi          #+#    #+#              #
#    Updated: 2024/02/21 10:56:47 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FUNC = pipex.c \
			pipex_utils.c \
			pipex_utils2.c \

FUNC_BONUS = pipex_bonus.c \
				pipex_utils_bonus.c \
				pipex_utils2_bonus.c \
				open_file_bonus.c \
				here_doc_bonus.c \

OBJ = ${FUNC:.c=.o}

OBJ_BONUS = ${FUNC_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJ} .mandatory
	@rm -f ${OBJ_BONUS}
	@make re -C ./libft
	@cc ${OBJ} -Llibft -lft -o ${NAME}

.mandatory: 
	@rm -f .bonus
	@touch .mandatory

%.o: %.c
	cc ${CFLAGS} -c $< -o $@

bonus: .bonus

.bonus: ${OBJ_BONUS}
	@rm -f ${OBJ}
	@make re -C ./libft
	@cc ${OBJ_BONUS} -Llibft -lft -o ${NAME}
	@rm -f .mandatory
	@touch .bonus

clean:
	@make clean -C ./libft
	@rm -f .mandatory
	@rm -f .bonus
	rm -f ${OBJ} ${OBJ_BONUS}

fclean: clean
	@make fclean -C ./libft
	rm -f ${NAME}

re: fclean all

re_bonus: fclean bonus

.PHONY: all, clean, fclean, re, bonus, re_bonus
