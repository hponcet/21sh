/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 20:09:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/07 20:13:19 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_tabjoin(char **tb)
{
	int		i;
	char	*ret;

	i = 0;
	if (!tb)
		return (NULL);
	while (tb[i])
	{
		ret = ft_joinf("%s%s", ret, tb);
		i++;
	}
	return (ret);
}
