/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:09:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 11:00:01 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	if (!s1[i])
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	else
	{
		while (i < n && s1[i] && (s1[i] == s2[i]))
			i++;
		if (i == n)
			return (0);
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
