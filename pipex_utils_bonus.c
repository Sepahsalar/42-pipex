/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 16:15:37 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_path_con(char **total_paths, char *cmd, char *temp)
{
	char	*final_path;

	while (*total_paths)
	{
		temp = ft_strjoin(*total_paths, "/");
		if (!temp)
		{
			ft_free(total_paths);
			error(EXIT_FAILURE);
		}
		final_path = ft_strjoin(temp, cmd);
		if (!final_path)
		{
			free(temp);
			ft_free(total_paths);
			error(EXIT_FAILURE);
		}
		free(temp);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		total_paths++;
	}
	return (0);
}

static char	*get_path(char *cmd, char **envp)
{
	char	**total_paths;
	char	*final_path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (!*envp)
	{
		ft_putstr_fd("Error: command not found: \n", STDERR_FILENO);
		exit(127);
	}
	total_paths = ft_split(*envp + 5, ':');
	if (!total_paths)
		error(EXIT_FAILURE);
	final_path = get_path_con(total_paths, cmd, NULL);
	if (!final_path)
	{
		ft_free(total_paths);
		return (NULL);
	}
	ft_free(total_paths);
	return (final_path);
}

void	check_space(char *argv)
{
	char	*temp;

	temp = ft_strtrim(argv, " ");
	if (temp[0] == '\0')
	{
		ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
		ft_putendl_fd(argv, STDERR_FILENO);
		exit(127);
	}
}

void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	check_space(argv);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error(EXIT_FAILURE);
	if (!ft_strchr(cmd[0], '/') && (cmd[0][0] != '.' && cmd[0][1] != '/'))
		path = get_path(cmd[0], envp);
	else
	{
		clean_cmd(cmd[0]);
		path = cmd[0];
	}
	if (!path)
	{
		ft_free(cmd);
		ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
		ft_putendl_fd(argv, STDERR_FILENO);
		exit(127);
	}
	else
	{
		if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == -1)
		{
			if (path != cmd[0])
				free(path);
			error(126);
		}
		if (execve(path, cmd, envp) == -1)
			error(EXIT_FAILURE);
	}
}
