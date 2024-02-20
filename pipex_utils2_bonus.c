/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:31:40 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 12:08:52 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	find_max(char *argv, char *str)
{
	size_t	max;

	if (ft_strlen(argv) > ft_strlen(str))
		max = ft_strlen(argv);
	else
		max = ft_strlen(str);
	return (max);
}

void	error(int status)
{
	perror("Error");
	exit(status);
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
