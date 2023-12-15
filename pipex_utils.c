/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:33 by asohrabi          #+#    #+#             */
/*   Updated: 2023/12/15 20:10:01 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *msg)
{
	perror(msg);
	exit(1);
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

char	*get_path_con(char **total_paths, char *cmd, char *temp, int i)
{
	char	*final_path;

	i = 0;
	while (total_paths[i])
	{
		temp = ft_strjoin(total_paths[i], "/");
		if (!temp)
		{
			ft_free(total_paths);
			error("Error: Joining failed");
		}
		final_path = ft_strjoin(temp, cmd);
		if (!final_path)
		{
			free(temp);
			ft_free(total_paths);
			error("Error: Joining failed");
		}
		free(temp);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (0);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**total_paths;
	char	*temp;
	char	*final_path;

	i = 0;
	temp = NULL;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	total_paths = ft_split(envp[i] + 5, ':');
	if (!total_paths)
		error("Error: Splitting failed");
	final_path = get_path_con(total_paths, cmd, temp, i);
	if (!final_path)
	{
		ft_free(total_paths);
		free(temp);
		return (NULL);
	}
	else
		return (final_path);
	ft_free(total_paths);
	return (0);
}

void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("Error: Splitting failed");
	path = get_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		error("Error: Getting path failed!");
	}
	if (execve(path, cmd, envp) == -1)
		error("Error: Executing Command Failed!");
}
