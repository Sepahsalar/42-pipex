/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:40:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/02/20 16:12:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static char	*delete_backslash(char *str)
{
	char	*src;
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	src = str;
	dst = str;
	while (src[i])
	{
		if (src[i] != '\\')
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

void	clean_cmd(char *str)
{
	int	i;

	i = 0;
	str = delete_backslash(str);
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
