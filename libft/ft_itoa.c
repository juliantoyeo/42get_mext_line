/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:51:51 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/15 23:48:14 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_intlen(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void		fill_itoa(char *str, int n, int is_neg, int size)
{
	str[size] = '\0';
	while (size-- >= 0)
	{
		if (size == 0 && is_neg == -1)
			str[size] = '-';
		else if (n < -2147483647)
		{
			str[size] = '8';
			n = 2147483647;
		}
		else
			str[size] = ((n % 10) + 48);
		n = n / 10;
	}
}

char			*ft_itoa(int n)
{
	int		size;
	int		is_negative;
	char	*str;

	is_negative = 0;
	size = get_intlen(n);
	if (n < 0)
	{
		is_negative = -1;
		n = n * is_negative;
	}
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill_itoa(str, n, is_negative, size);
	return (str);
}
