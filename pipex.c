/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 18:43:36 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// handle open file errors, quotations and \ and /
// It would be reasonable to write a function for cmd not found
// when an error occured, do not exit the program
// handle this: ./pipex int te wcl out1 for bonus part
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		wait;

	status = 0;
	if (argc != 5)
	{
		ft_putendl_fd("Error: Wrong Arguments!", STDERR_FILENO);
		ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (pipe(fd) == -1)
			error(EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			error(EXIT_FAILURE);
		if (pid == 0)
			first_child_process(fd, argv, envp);
		else
		{
			status = second_child_process(fd, argv, envp);
			waitpid(pid, &wait, 0);
		}
	}
	return (status);
}
