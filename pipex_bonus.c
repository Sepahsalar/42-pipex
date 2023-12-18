/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:21 by asohrabi          #+#    #+#             */
/*   Updated: 2023/12/18 17:45:51 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		// close(fd[1]);
		execute_cmd(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		// close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Wrong Arguments!\n", 2);
		ft_putstr_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
		ft_putstr_fd("Ex: ./pipex \"here_doc\" LIMITER cmd cmd1 outfile\n", 2);
		return (1);
	}
	else
	{
		if (argv[1] == "here_doc")
		{
			i = 3;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fileout == -1)
				error();
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fileout == -1)
				error();
			filein = open(argv[1], O_RDONLY, 0777);
			if (filein == -1)
				error();
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute_cmd(argv[argc - 2], envp);
	}
	return (0);
}
