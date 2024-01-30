/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:03:14 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 10:57:26 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_putnum(const char *str, int sign, int i)
{
	long	a;

	a = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - '0');
		if (a < 0 && sign == 1)
			return (-1);
		else if (a < 0 && sign == -1)
			return (0);
		i++;
	}
	return (sign * (int)a);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;

	i = 0;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == '\v')
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == ' '))
		i++;
	sign = 1;
	return (ft_putnum(str, sign, i));
}
