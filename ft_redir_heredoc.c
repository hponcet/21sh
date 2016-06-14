/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 22:44:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/14 16:59:35 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int		ft_redir_heredoc_hd(char **cmd)
{
	char	*word;
	int		i;

	i = ft_cindex_rev(*cmd, '<');
	while (cmd[0][i] == '<' || cmd[0][i] == ' ' || cmd[0][i] == '\t')
		i++;
	word = ft_strsub(*cmd, i, ft_strlen(*cmd) - i);
	g_curs.hd = word;
	g_curs.hd_cmd = ft_strsub(*cmd, 0, ft_cindex(*cmd, '<') - 1);
	ft_hist_addtohist(g_retval);
	ft_strdel(&g_retval);
	ft_strdel(cmd);
	ft_putstr("heredoc> ");
	return (1);
}

static int		ft_redir_heredoc_return(char *cmd, int i)
{
	if (i == 1)
	{
		ft_strdel(&g_retval);
		ft_strdel(&cmd);
		ft_putstr("hededoc> ");
		return (1);
	}
	else
	{
		ft_strdel(&g_retval);
		g_retval = ft_strdup(g_curs.hd_cmd);
		ft_strdel(&g_curs.hd_cmd);
		ft_strdel(&g_curs.hd);
		ft_strdel(&cmd);
		return (0);
	}
}

static void		ft_redir_heredoc_joininput(char *input)
{
	if (g_curs.hd_input)
		ft_joinf("%xs\n%s", g_curs.hd_input, input);
	else
		g_curs.hd_input = ft_strdup(input);
}

int				ft_redir_heredoc(void)
{
	int		i;
	char	*cmd;

	cmd = NULL;
	if (!g_retval)
	{
		ft_putstr("heredoc> ");
		return (1);
	}
	cmd = ft_strdup(g_retval);
	if (((i = ft_cindex(cmd, '<')) > 0 && cmd[i + 1] == '<') || g_curs.hd != NULL)
	{
		if (!g_curs.hd && ft_redir_heredoc_hd(&cmd) == 1)
			return (1);
		else
		{
			if (ft_strcmp(g_retval, g_curs.hd) == 0)
				return (ft_redir_heredoc_return(cmd, 0));
			else
				return (ft_redir_heredoc_return(cmd, 1));
		}
	}
	ft_strdel(&cmd);
	return (0);
}
