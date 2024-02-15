/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/15 16:34:00 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// handle open file errors, permission, quotations and \ and /
// for permission I should change the error function, or
// write a function for just that case
// It would be reasonable to write a function for cmd not found
void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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
			error();
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
			first_child_process(fd, argv, envp);
		// else
		// {
			status = second_child_process(fd, argv, envp);
			waitpid(pid, &wait, 0);
		// }
	}
	exit (status);
}
