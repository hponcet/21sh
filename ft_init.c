/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:49:03 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/01 18:12:22 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_load(void)
{
	get_fd();
	ft_term_init();
	ft_put_name();
	g_curs.curs_pos = (int*)malloc(sizeof(int) * 2);
	g_initpos = (int*)malloc(sizeof(int) * 2);
	g_curs.ws = (int*)malloc(sizeof(int) * 2);
	g_curs.ls = NULL;
	g_curs.select = NULL;
	g_curs.qt = 0;
	g_curs.hd = NULL;
	g_curs.hd_cmd = NULL;
	ft_cursor_pos();
	g_initpos[0] = g_curs.curs_pos[0];
	g_initpos[1] = g_curs.curs_pos[1];
	g_chain = NULL;
	g_tmpchain = NULL;
	g_copy = NULL;
	g_retval = NULL;
	g_hist = NULL;
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
	if (g_retval)
		ft_init_hist();
	ft_cursor_pos();
	g_initpos[0] = g_curs.curs_pos[0];
	g_initpos[1] = g_curs.curs_pos[1];
}

void	ft_init_window(void)
{
	ft_window_size();
}
