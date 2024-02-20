/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:49 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 15:48:12 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

void	error(int status);
void	ft_free(char **array);
void	execute_cmd(char *argv, char **envp);
void	first_child_process(int *fd, char **argv, char **envp);
int		second_child_process(int *fd, char **argv, char **envp);
void	clean_cmd(char *str);

#endif
