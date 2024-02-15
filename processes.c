/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:26:48 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/15 12:54:03 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	status_check(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS (status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (1);
}

void	first_child_process(int *fd, char **argv, char **envp)
{
	int		filein;

	close(fd[0]);
	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error();
		// exit (0);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	if (dup2(filein, STDIN_FILENO) == -1)
		error();
	close(fd[1]);
	close(filein);
	execute_cmd(argv[2], envp);
}

int	second_child_process(int *fd, char **argv, char **envp)
{
	int		fileout;
	pid_t	child_pid;
	int		status;

	status = 0;
	close(fd[1]);
	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fileout == -1)
		error();
		// exit (0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error();
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error();
	close(fd[0]);
	close(fileout);
	child_pid = fork();
	if (child_pid == -1)
		error();
	else if (child_pid == 0)
		execute_cmd(argv[3], envp);
	else
		waitpid(child_pid, &status, 0);
	return (status_check(status));
}
