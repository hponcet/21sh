/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 20:13:10 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/20 20:30:17 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_cmd_v(char *buf)
{
	int		i;

	i = 0;
	if (buf[5] != 0)
	{
		while (buf[i] != 0)
		{
			if (buf[i] == '\n')
			{
				ft_chain_addchar(' ');
				i++;
				continue ;
			}
			if (ft_isprint(buf[i]))
				ft_chain_addchar(buf[i]);
			i++;
		}
	}
}