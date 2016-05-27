/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 07:10:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/21 13:30:04 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_up(void)
{
	if (!g_hist)
		return ;
	if (g_hist->prev && g_curs.hist == 1)
		g_hist = g_hist->prev;
	else if (g_curs.hist == 0)
		g_curs.hist = 1;
	tputs(tgoto(tgetstr("cm", 0), g_initpos[0] - 1, g_initpos[1] - 1), 1, ft_char);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	ft_putstr_fd(g_hist->cmd, g_fd);
	if ((int)ft_strlen(g_hist->cmd) + g_initpos[0] >
			g_curs.ws[0] && g_curs.ws[1] == g_initpos[1])
		g_initpos[1] -= ((int)ft_strlen(g_hist->cmd) + g_initpos[0]) /
			g_curs.ws[0];
	if (g_curs.hist == 0)
	{
		g_curs.hist = 1;
		return ;
	}
}
