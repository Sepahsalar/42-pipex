/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:41 by asohrabi          #+#    #+#             */
/*   Updated: 2023/12/13 16:46:35 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		
	}
}
