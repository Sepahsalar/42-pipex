/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:21 by asohrabi          #+#    #+#             */
/*   Updated: 2023/12/19 21:18:23 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		close(fd[1]);
		execute_cmd(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	open_file(char *argv, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(argv, O_RDONLY, 0777);
	else if (i == 1)
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		error();
	return (fd);
}

void	here_doc(char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	else if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("pipe heredoc> ", 1);
			line = get_next_line(0);
			if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			{
				free(line);
				exit(0);
			}
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]); //maybe delete
		wait(NULL); //maybe waitpid
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

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
		dup2(filein, STDIN_FILENO);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	execute_cmd(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_putstr_fd("Error: Wrong Arguments!\n", 2);
		ft_putstr_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
		ft_putstr_fd("Ex: ./pipex \"here_doc\" LIMITER cmd cmd1 outfile\n", 2);
		exit(1);
	}
	else
		pipex(argc, argv, envp);
	return (0);
}
