/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:43:21 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 10:58:07 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cal(char *result, int count, int nbr)
{
	int	i;
	int	n;
	int	temp;

	n = nbr;
	i = count - 1;
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	if (n < 0)
		temp = 1;
	else
		temp = 0;
	while (i >= temp)
	{
		result[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
	result[count] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		count;
	int		nbr;

	nbr = n;
	count = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	result = (char *)malloc((count + 1) * sizeof(char));
	if (!result)
		return (0);
	return (ft_cal(result, count, nbr));
}
