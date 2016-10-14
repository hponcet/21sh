/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:20:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/14 15:29:10 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_compl_display(t_compl *print)
{
	int		i;
	t_compl	*tmp;

	tmp = print;
	g_curs.tb += 1;
	ft_putnbr(g_curs.tb);
	i = g_curs.tb - 1;
	tputs(tgetstr("sc", 0), 1, ft_char);
	while (i > 1 && tmp)
		tmp = tmp->next;
	ft_putstr(tmp->name);
	tputs(tgetstr("rc", 0), 1, ft_char);
}

