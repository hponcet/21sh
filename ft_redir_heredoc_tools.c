/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:18:30 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/29 16:11:12 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int				ft_heredoc_check(void)
{
	int		i;

	i = ft_cindex_rev(g_curs.retval, '<');
	if (i > 1 && g_curs.retval[i - 1] == '<')
		return (i);
	else
		return (-1);
}

void			ft_heredoc_del(void)
{
	int		fd;

	fd = -1;
	if (!g_curs.hd)
		return ;
	fd = open("/tmp/.__21sh_tmp_hd", O_TRUNC | O_RDWR);
	close(fd);
	ft_strdel(&(g_curs.hd->cmd));
	ft_strdel(&(g_curs.hd->init_cmd));
	ft_strdel(&(g_curs.hd->trigger));
	free(g_curs.hd);
	g_curs.hd = NULL;
}
