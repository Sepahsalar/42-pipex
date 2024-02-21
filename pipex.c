/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/21 10:36:29 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// handle quotations
// when an error occured, do not exit the program
// handle this: ./pipex int te wcl out1 for bonus part
static int	status_check(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS (status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (1);
}

static void	first_child_process(int *fd, char **argv, char **envp)
{
	int	filein;

	close(fd[0]);
	if (access(argv[1], F_OK | R_OK) == -1)
		error(EXIT_SUCCESS);
	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error(EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error(EXIT_FAILURE);
	if (dup2(filein, STDIN_FILENO) == -1)
		error(EXIT_FAILURE);
	close(fd[1]);
	close(filein);
	execute_cmd(argv[2], envp);
}

static int	second_child_process(int *fd, char **argv, char **envp)
{
	int		fileout;
	pid_t	pid;
	int		status;

	status = 0;
	close(fd[1]);
	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
		error(EXIT_FAILURE);
	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error(EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error(EXIT_FAILURE);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error(EXIT_FAILURE);
	close(fd[0]);
	close(fileout);
	pid = fork();
	if (pid == -1)
		error(EXIT_FAILURE);
	if (pid == 0)
		execute_cmd(argv[3], envp);
	else
		waitpid(pid, &status, 0);
	return (status_check(status));
}

static void	args_error(void)
{
	ft_putendl_fd("Error: Wrong Arguments!", STDERR_FILENO);
	ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		wait;

	status = 0;
	if (argc != 5)
		args_error();
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
