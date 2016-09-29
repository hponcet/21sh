/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:58:21 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/29 15:19:11 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void ft_key_ctrl_d(void)
{
	if (g_curs.hd)
	{
		ft_putendl("");
		ft_heredoc_addcontent(g_curs.retval);
		ft_heredoc_exec(g_curs.hd->trigger);
		ft_heredoc_del();
		ft_put_name();
		ft_init();
	}
	else if (g_curs.qt == 1)
		;
	else if (!g_curs.retval)
		exit(0);
}

static void	ft_reinit_hist(void)
{
	ft_histtochain();
	ft_init_pos();
	ft_count_chain();
	g_curs.hist = 0;
	g_curs.next = NULL;
	g_curs.prev = g_curs.ls;
}

void		ft_key_group_dir(char *buf)
{
	if (buf[1] == 91 && buf[2] == 51 && buf[3] == 126 && buf[4] == 0 && g_curs.chain)
		ft_key_del();
	if (buf[1] == 91 && buf[2] >= 65 && buf[2] <= 68 && buf[3] == 0)
		ft_key_directional(buf);
	if (buf[1] == 27 && buf[2] == 91 && buf[3] >= 65 && buf[3] <= 68 && g_curs.chain)
		ft_key_opt_directional(buf);
	if (buf[1] == 91 && buf[2] == 49 && buf[3] == 59 && buf[5] == 67 && g_curs.chain)
		ft_shift_dir_right();
	if (buf[1] == 91 && buf[2] == 49 && buf[3] == 59 && buf[5] == 68 && g_curs.chain)
		ft_shift_dir_left();
	if (buf[1] == 91 && (buf[2] == 70 || buf[2] == 72) && g_curs.chain)
		ft_key_home(buf);
}

void		ft_key(char *buf)
{
	if (g_curs.hist == 1 && (buf[0] != 27 || buf[1] != 91 ||
				(buf[2] != 65 && buf[2] != 66)))
		ft_reinit_hist();
	if (g_curs.select && (buf[0] != -30 && buf[0] != -61 && buf[3] != 59))
		ft_reset_select();
	if (buf[0] == 10)								/// Enter
		ft_key_enter();
	else if (buf[0] == 4 && buf[1] == 0)
		ft_key_ctrl_d();
	else if (buf[0] == -30 || buf[0] == -61)
		ft_func_copy(buf);
	else if (ft_isprint(buf[0]) == 1 && buf[1] == 0)			/// alpha
		ft_chain_addchar(buf[0]);
	else if (buf[0] == 127 && buf[1] == 0 && g_curs.chain)	/// bs
		ft_key_bs();
	else if (buf[0] == 27)					/// directional
		ft_key_group_dir(buf);
	else
		ft_cmd_v(buf);
	if (__DEBUG__ == "Y")
		ft_debug();
	ft_cursor_pos();
	ft_count_chain();
	ft_init_pos();
}
