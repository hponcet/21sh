/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 16:18:52 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 20:11:06 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabdel(char **table)
{
	int		i;
	
	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		ft_strdel(&(table[i]));
		i++;
	}
	free(table);
}
