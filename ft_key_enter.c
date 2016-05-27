/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_enter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 09:09:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/21 15:21:36 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_enter(void)
{

	ft_putendl_fd("", g_fd);
	if (!g_retval && g_curs.qt == 0)
	{
		ft_put_name();
		ft_init();
		return ;
	}
	if (ft_quote() > 0)
	{
		g_curs.qt = 1;
		ft_init();	
		return ;
	}
	ft_cmd();
	ft_hist_addtohist(g_retval);
	ft_put_name();
	ft_init();
}
