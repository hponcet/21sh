/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 04:57:17 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/20 20:32:06 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_display(void)
{
	char	buf[__BUFLEN__];

	ft_signal();
	while (42)
	{
		ft_key(buf);
		ft_bzero(buf, __BUFLEN__);
		read(g_fd, buf, __BUFLEN__);
	}
}
