/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:21 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 11:37:16 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(char *argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error(EXIT_FAILURE);
		close(fd[1]);
		execute_cmd(argv, envp);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error(EXIT_FAILURE);
		close(fd[0]);
	}
}

static int	open_file(char *argv, int i)
{
	int	fd;

	if (i == 0)
	{
		if (access(argv, F_OK) == -1)
			error(EXIT_SUCCESS);
		if (access(argv, R_OK) == -1)
			error(EXIT_FAILURE);
		fd = open(argv, O_RDONLY);
	}
	else if (i == 1)
	{
		if (access(argv, F_OK) == 0 && access(argv, W_OK) == -1)
			error(EXIT_FAILURE);
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else
	{
		if (access(argv, F_OK) == 0 && access(argv, W_OK) == -1)
			error(EXIT_FAILURE);
		fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	if (fd == -1)
		error(EXIT_FAILURE);
	return (fd);
}

static int	status_check(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS (status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (1);
}

static int	pipex(int argc, char **argv, char **envp)
{
	int		i;
	int		filein;
	int		fileout;
	int		status;

	status = 0;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		i = 3;
		fileout = open_file(argv[argc - 1], 2);
		here_doc(argv[2]);
	}
	else
	{
		i = 2;
		fileout = open_file(argv[argc - 1], 1);
		filein = open_file(argv[1], 0);
		if (dup2(filein, STDIN_FILENO) == -1)
			error(EXIT_FAILURE);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error(EXIT_FAILURE);
	execute_cmd(argv[argc - 2], envp);
	wait(&status);
	// waitpid(pid, &status, 0);
	return (status_check(status));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0
			&& argc < 6))
	{
		ft_putendl_fd("Error: Wrong Arguments!", STDERR_FILENO);
		ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile",
			STDERR_FILENO);
		ft_putendl_fd("Ex: ./pipex \"here_doc\" LIMITER cmd cmd1 outfile",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
		pipex(argc, argv, envp);
	return (0);
}
