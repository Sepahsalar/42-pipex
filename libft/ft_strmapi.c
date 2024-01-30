/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:54:03 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 10:59:57 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*array;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	array = (char *)malloc((len + 1) * sizeof(char));
	if (!array)
		return (0);
	i = 0;
	while (i < len)
	{
		array[i] = f(i, s[i]);
		i++;
	}
	array[len] = '\0';
	return (array);
}
