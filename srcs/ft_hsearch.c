/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsearch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 06:14:59 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 06:32:57 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_hsearch_display()
{
	char	*buf;
	int		x;
	int		y;

	x = g_curs.init_pos[0];
	y = g_curs.init_pos[1];
	buf = ft_strnew(4);
	ft_putendl_fd("", g_curs.fd);
	ft_putstr_fd("search:", g_curs.fd);
	while (42)
	{
		ft_bzero(buf, 4);
		read(g_curs.fd, buf, 4);
	}
	ft_strdel(&buf);
}
