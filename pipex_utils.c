/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:33 by asohrabi          #+#    #+#             */
/*   Updated: 2023/12/18 18:10:22 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
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
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
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
		error();
	if (!ft_strchr(cmd[0], '/') && (cmd[0][0] != '.' && cmd[0][1] != '/'))
		path = get_path(cmd[0], envp);
	else
		path = cmd[0];
	if (!path)
	{
		ft_free(cmd);
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(argv, 2);
		exit(1);
	}
	if (execve(path, cmd, envp) == -1)
		error();
}
