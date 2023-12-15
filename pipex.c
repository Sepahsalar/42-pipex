/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:41 by asohrabi          #+#    #+#             */
/*   Updated: 2023/12/15 18:34:31 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error("Error: Opening file failed!");
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute_cmd(argv[2], envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	fileout;

	fileout = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fileout == -1)
		error("Error: Opening file failed!");
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong Arguments!\n", 2);
		ft_putstr_fd("Ex: ./pipex infile cmd1 cmd2 outfile\n", 1);
	}
	else
	{
		if (pipe(fd) == -1)
			error("Error: Piping failed!");
		pid = fork();
		if (pid == -1)
			error("Error: Forking failed!");
		else if (pid == 0)
			child_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
	}
}
