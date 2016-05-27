/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 17:55:27 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/18 17:39:30 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_countnbr(int nb)
{
	size_t		i;

	i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	int				i;
	int				sign;
	char			*buf;

	if (n == (-2147483648))
		return (ft_strdup("-2147483648"));
	buf = ft_strnew(ft_countnbr(n));
	if (!buf)
		return (NULL);
	sign = n;
	n *= (n < 0) ? -1 : 1;
	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n > 0)
	{
		buf[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		buf[i++] = '-';
	buf[i] = '\0';
	return (ft_strrvrs(buf));
}
