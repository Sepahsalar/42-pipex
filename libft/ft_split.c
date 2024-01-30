/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:30:45 by asohrabi          #+#    #+#             */
/*   Updated: 2024/01/30 10:59:23 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_occur(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (in_word == 1)
			{
				count++;
				in_word = 0;
			}
		}
		else
		{
			if (in_word == 0)
				in_word = 1;
		}
		s++;
	}
	if (in_word == 1)
		count++;
	return (count);
}

static char	**fill_subarr(int index, char **array, char *str, char *word_start)
{
	int		i;

	i = 0;
	array[index] = (char *)malloc(((str - word_start) + 1) * sizeof(char));
	if (!array[index])
	{
		while (i < index)
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (0);
	}
	i = 0;
	while (i < (str - word_start))
	{
		array[index][i] = word_start[i];
		i++;
	}
	array[index][str - word_start] = '\0';
	return (array);
}

static t_shorten	first_split(char *str, char c)
{
	t_shorten	p;

	p = (t_shorten){0, 0, 0, str, 0};
	p.array = (char **)malloc((count_occur(str, c) + 1) * sizeof(char *));
	if (!p.array)
		return (p);
	while (*p.s)
	{
		if (*p.s == c)
		{
			if (p.in_word)
			{
				p.array = fill_subarr(p.index, p.array, p.s, p.word_start);
				p.index++;
				p.in_word = 0;
			}
		}
		else if (!p.in_word)
		{
			p.in_word = 1;
			p.word_start = p.s;
		}
		p.s++;
	}
	return (p);
}

char	**ft_split(char const *s, char c)
{
	t_shorten	p;

	if (!s)
		return (0);
	p = first_split((char *)s, c);
	if (!p.array)
		return (0);
	if (p.in_word)
	{
		p.array = fill_subarr(p.index, p.array, p.s, p.word_start);
		p.index++;
	}
	p.array[p.index] = 0;
	return (p.array);
}
