/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:33 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/12 18:29:29 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_con(char **total_paths, char *cmd, char *temp, int i)
{
	char	*final_path;

	i = 0;
	while (total_paths[i])
	{
		temp = ft_strjoin(total_paths[i], "/");
		if (!temp)
		{
			ft_free(total_paths);
			error();
		}
		final_path = ft_strjoin(temp, cmd);
		if (!final_path)
		{
			free(temp);
			ft_free(total_paths);
			error();
		}
		free(temp);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (0);
}

static char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**total_paths;
	char	*temp;
	char	*final_path;

	i = 0;
	temp = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
	{
		ft_putstr_fd("Error: command not found: \n", STDERR_FILENO);
		exit(127);
	}
	total_paths = ft_split(envp[i] + 5, ':');
	if (!total_paths)
		error();
	final_path = get_path_con(total_paths, cmd, temp, i);
	if (!final_path)
	{
		ft_free(total_paths);
		free(temp);
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
		error();
	if (!ft_strchr(cmd[0], '/') && (cmd[0][0] != '.' && cmd[0][1] != '/'))
		path = get_path(cmd[0], envp);
	else
		path = cmd[0];
	if (!path)
	{
		ft_free(cmd);
		ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
		ft_putendl_fd(argv, STDERR_FILENO);
		exit(127);
	}
	else
	{
		if (execve(path, cmd, envp) == -1)
			error();
	}
}
