/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:37:12 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:01 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_helper(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, find_max(line, limiter)) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
}

void	here_doc(char *limiter)
{
	int		fd[2];
	pid_t	pid;

	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		error(EXIT_FAILURE);
	if (pipe(fd) == -1)
		error(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error(EXIT_FAILURE);
	if (pid == 0)
		here_doc_helper(fd, limiter);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error(EXIT_FAILURE);
		close(fd[0]);
		//wait(NULL); // maybe not right
	}
}
