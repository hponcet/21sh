/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 08:52:16 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/08 16:27:25 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_down(void)
{
	if (!g_hist || g_curs.hist == 0)
		return ;
	tputs(tgoto(tgetstr("cm", 0), g_initpos[0] - 1, 
				g_initpos[1] - 1), 1, ft_char);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	if (g_curs.hist == 1 && !g_hist->next)
	{
		g_curs.hist = 0;
		if (g_chain)
		{
			ft_str_tc(g_chain);
			ft_count_chain();
			ft_init_pos();
			tputs(tgoto(tgetstr("cm", 0), g_curs.ls->cp[0], g_curs.ls->
						cp[1] - 1), 1, ft_char);
		}
		return ;
	}
	if (g_hist->next)
	{
		g_hist = g_hist->next;
		ft_putstr_fd(g_hist->cmd, g_fd);
	}
}
