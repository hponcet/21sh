/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:20:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 02:30:20 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_compl_countfile(t_compl *print)
{
	t_compl	*tmp;
	int		count;

	count = 0;
	tmp = print;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void		ft_compl_display(t_compl *print, char *find)
{
	char	*buf;
	t_compl	*tmp;
	int		x;
	int		y;

	x = g_curs.curs_pos[0];
	y = g_curs.curs_pos[1];
	if (!find)
		find = ft_strnew(0);
	tmp = print;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = print;
	tmp = print;
	tputs(tgoto(tgetstr("cm", 0), x - 1, y - 1), 1, ft_char);
	ft_putstr(print->name + ft_strlen(find));
	tputs(tgetstr("ce", 0), 1, ft_char);
	buf = ft_strnew(4);
	while (42)
	{
		if (ft_compl_key(buf, &tmp, find, x, y) == 1)
			break ;
		ft_bzero(buf, 4);
		read(g_curs.fd, buf, 4);
	}
}
