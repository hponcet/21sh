/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 22:44:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/15 15:14:55 by hponcet          ###   ########.fr       */
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

static void		ft_redir_heredoc_joininput(char *cmd)
{
	if (ft_strcmp(cmd, g_curs.hd) == 0)
		return ;
	if (!g_curs.hd_input)
		g_curs.hd_input = ft_strdup(cmd);
	else
		g_curs.hd_input = ft_joinf("%xs\n%s", g_curs.hd_input, cmd);
}

static void		ft_redir_heredoc_exec(void)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	ft_putendl_fd(g_curs.hd_input, fd[1]);
	ft_signal_onexec();
	pid = fork();
	g_cmd = ms_get_cmd(g_curs.hd_cmd);
	if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		ms_exec_bin(ms_search_bin(g_env), g_env);
	}
	ft_put_name();
	ft_init();
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
		ft_redir_heredoc_exec();
		ft_strdel(&g_retval);
		ft_strdel(&cmd);
		ft_strdel(&g_curs.hd);
		ft_strdel(&g_curs.hd_cmd);
		ft_strdel(&g_curs.hd_input);
		return (0);
	}
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
			ft_redir_heredoc_joininput(cmd);
			if (ft_strcmp(g_retval, g_curs.hd) == 0)
				return (ft_redir_heredoc_return(cmd, 0));
			else
				return (ft_redir_heredoc_return(cmd, 1));
		}
	}
	ft_strdel(&cmd);
	return (0);
}
