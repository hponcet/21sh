/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:20:26 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/15 12:27:09 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_window_size(void)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	g_curs.ws[0] = win.ws_col;
	g_curs.ws[1] = win.ws_row;
}
