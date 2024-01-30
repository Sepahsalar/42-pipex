/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:41:18 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 11:00:16 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	real_len;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		real_len = ft_strlen(s) - start;
	else
		real_len = len;
	sub = (char *)malloc((real_len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (i < real_len)
	{
		sub[i] = ((char *)s)[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
