/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:41 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 11:07:33 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int *fd, char **argv, char **envp)
{
	int		filein;

	close(fd[0]);
	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	if (dup2(filein, STDIN_FILENO) == -1)
		error();
	close(fd[1]);
	close(filein);
	execute_cmd(argv[2], envp);
}

static void	parent_process(int *fd, char **argv, char **envp)
{
	int		fileout;
	pid_t	child_pid;

	close(fd[1]);
	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
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
		waitpid(child_pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong Arguments!\n", STDERR_FILENO);
		ft_putstr_fd("Ex: ./pipex infile cmd1 cmd2 outfile\n", STDERR_FILENO);
		exit(1);
	}
	else
	{
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
			child_process(fd, argv, envp);
		// waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
