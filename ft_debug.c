/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 08:48:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/08 11:51:19 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_debug(void)
{
	int		i;

	i = 0;
	ft_cursor_pos();
	tputs(tgoto(tgetstr("sc", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ho", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	while (i < g_curs.ws[0]) {
		if (i == ((g_curs.ws[0] / 2) - 3)){
			ft_putstr(" DEBUG ");
			i += 7;
		}
		ft_putchar('#');
		i++;
	}
	/////////////////// last_char ////////////////////
	if (g_chain)
	{
		ft_putstr_fd("last_char = ", g_fd);
		ft_putchar_fd(g_curs.ls->c, g_fd);
		ft_putstr_fd(" / cp :", g_fd);
		ft_putnbr_fd(g_curs.ls->cp[0], g_fd);
		ft_putstr_fd("/", g_fd);
		ft_putnbr_fd(g_curs.ls->cp[1], g_fd);
	}
	
	/////////////////// g_error /////////////////////
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("g_error = ", g_fd);
	ft_putnbr_fd(g_error, g_fd);
	
	/////////////////// Cursor /////////////////// 
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("Cursor : cur_pos = ", g_fd);
	ft_putnbr_fd(g_curs.curs_pos[0], g_fd);
	ft_putstr_fd("/", g_fd);
	ft_putnbr_fd(g_curs.curs_pos[1], g_fd);
	ft_putstr_fd(" P&Nchar = ", g_fd);
	if (g_curs.prev)
		ft_putchar_fd(g_curs.prev->c, g_fd);
	ft_putnbr_fd(g_curs.id, g_fd);
	if (g_curs.next)
		ft_putchar_fd(g_curs.next->c, g_fd);
	if (g_curs.prev)
	{
		ft_putstr_fd(" prev_pos = ", g_fd);
		ft_putnbr_fd(g_curs.prev->cp[0], g_fd);
		ft_putstr_fd("/", g_fd);
		ft_putnbr_fd(g_curs.prev->cp[1], g_fd);
	}

	/////////////////// g_chain /////////////////// 
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	if (g_chain)
	{
		ft_putstr_fd("g_chain : c = ", g_fd);
		ft_putchar_fd(g_chain->c, g_fd);
		ft_putstr_fd(" id = ", g_fd);
		ft_putnbr_fd(g_chain->id, g_fd);
		ft_putstr_fd(" cp = ", g_fd);
		ft_putnbr_fd(g_chain->cp[0], g_fd);
		ft_putstr_fd("/", g_fd);
		ft_putnbr_fd(g_chain->cp[1], g_fd);
	}

	/////////////////// Infos ////////////////////// 
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("Info : nb_chr = ", g_fd);
	ft_putnbr_fd(g_curs.nb_chr, g_fd);
	if (g_chain)
	{
		if (g_curs.prev && g_curs.prev->word == 1)
			ft_putstr_fd(" |word|", g_fd);
	}
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("Winsize = ", g_fd);
	ft_putnbr_fd(g_curs.ws[0], g_fd);
	ft_putstr_fd("/", g_fd);
	ft_putnbr_fd(g_curs.ws[1], g_fd);
	ft_putstr_fd(" g_initpos = ", g_fd);
	ft_putnbr_fd(g_initpos[0], g_fd);
	ft_putstr_fd("/", g_fd);
	ft_putnbr_fd(g_initpos[1], g_fd);
	
	/////////////////// g_hist ////////////////////// 
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("g_retval = ", g_fd);
	ft_printf("%s", g_retval);
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("g_copy = ", g_fd);
	if (g_hist)
		ft_printf("%s", g_copy);
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("g_moddedenv = ", g_fd);
	ft_printf("%i", g_moddedenv);
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("g_curs.hd = ", g_fd);
	ft_printf("%s", g_curs.hd);
	
	///////////////////// FOOT ////////////////////// 
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	i = 0;
	while (i < g_curs.ws[0]) {
		ft_putchar('#');
		i++;
	}
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("rc", 0), 1, 0), 1, ft_char);
	
//	///////////////////// Init Cursor ///////////////
//	if (g_curs.curs_pos[0] < 12)
//		g_curs.curs_pos[0] = 12;
}
