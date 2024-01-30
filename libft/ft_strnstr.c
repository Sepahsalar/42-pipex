/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:35:48 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 11:00:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && len == 0)
		return (0);
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while ((needle[j] == haystack[i + j]) && (i + j) < len)
		{
			if (!needle[j] && !haystack[i + j])
				return ((char *)(haystack + i));
			j++;
		}
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
