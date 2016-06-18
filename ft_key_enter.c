/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_enter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 09:09:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/13 22:45:38 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_enter(void)
{
	tcsetattr(3, TCSANOW, &(g_term.init));
	ft_putendl_fd("", g_fd);
	if (!g_retval && g_curs.qt == 0 && g_curs.hd == NULL)
	{
		ft_put_name();
		ft_init();
		return ;
	}
	if (g_curs.hd == NULL && ft_quote() > 0)
	{
		g_curs.qt = 1;
		ft_init();	
		return ;
	}
	if (ft_redir_heredoc() > 0 || g_curs.hd != NULL)
	{
		ft_init();
		return ;
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
