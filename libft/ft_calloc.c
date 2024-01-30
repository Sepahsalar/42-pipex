/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:42:44 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 10:57:38 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	max_size;

	max_size = 4611686014132420608;
	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (count != 0 && max_size / count < size)
		return ((void *)0);
	p = (void *)malloc(count * size * sizeof(void));
	if (!p)
		return ((void *)0);
	ft_bzero(p, count * size);
	return (p);
}
