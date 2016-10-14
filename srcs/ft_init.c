/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:49:03 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/14 01:25:22 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_load(void)
{
	get_fd();
	ft_term_init();
	ft_put_name();
	g_curs.curs_pos = (int*)malloc(sizeof(int) * 2);
	g_curs.initpos = (int*)malloc(sizeof(int) * 2);
	g_curs.ws = (int*)malloc(sizeof(int) * 2);
	g_curs.ls = NULL;
	g_curs.select = NULL;
	g_curs.qt = 0;
	ft_cursor_pos();
	g_curs.initpos[0] = g_curs.curs_pos[0];
	g_curs.initpos[1] = g_curs.curs_pos[1];
	g_curs.chain = NULL;
	g_curs.hd = NULL;
	g_curs.tmpchain = NULL;
	g_curs.copy = NULL;
	g_curs.retval = NULL;
	g_curs.history = NULL;
	ft_init_hist();
	ft_window_size();
	g_curs.nb_chr = 0;
	g_curs.id = 1;
	g_curs.next = NULL;
	g_curs.prev = NULL;
}

void	ft_init(void)
{
	ft_del_chain();
	g_curs.nb_chr = 0;
	g_curs.id = 1;
	g_curs.prev = NULL;
	g_curs.next = NULL;
	if (g_curs.retval)
	{
		ft_init_hist();
		ft_strdel(&g_curs.retval);
	}
	ft_cursor_pos();
	g_curs.initpos[0] = g_curs.curs_pos[0];
	g_curs.initpos[1] = g_curs.curs_pos[1];
	ft_signal();
}

void	ft_init_window(void)
{
	ft_window_size();
	tputs(tgoto(tgetstr("cl", 0), 1, 0), 1, ft_char);
	ft_put_name();
	if (g_curs.retval)
		ft_putstr_fd(g_curs.retval, g_curs.fd);
	ft_cursor_pos();
	ft_count_chain();
	ft_init_pos();
}

void	ft_init_prompt(void)
{
	ft_heredoc_del();
	g_curs.qt = 0;
	ft_strdel(&g_curs.tmpchain);
	g_curs.hist = 0;
	ft_putendl("");
	ft_put_name();
	ft_del_chain();
	ft_strdel(&g_curs.retval);
	ft_init();
}
