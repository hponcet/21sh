/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_enter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 09:09:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/15 16:31:26 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_enter(void)
{
	tcsetattr(3, TCSANOW, &(g_term.init));
	ft_putendl_fd("", g_fd);
	if (!g_retval && g_curs.qt == 0 && g_hd == NULL)
	{
		ft_put_name();
		ft_init();
		return ;
	}
	if (g_hd == NULL && ft_quote() > 0)
	{
		g_curs.qt = 1;
		ft_init();	
		return ;
	}
	if (ft_heredoc_check() > -1 || g_hd)
	{
		ft_heredoc_proc();
		ft_init();
		if (g_hd)
			return ;
		else
		{
			ft_put_name();
			ft_init();
			return ;
		}
	}
	if (!g_retval)
		return ;
	ft_signal_onexec();
	ft_cmd(g_retval);
	ft_hist_addtohist(g_retval);
	tcsetattr(3, TCSANOW, &(g_term.mod));
	ft_put_name();
	ft_init();
}
