/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 22:44:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/27 12:54:21 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void			ft_heredoc_err(int i)
{
	if (i == 0)
		ft_putendl_fd("heredoc: Bad command.", g_curs.fd);
	if (i == 1)
	{
		ft_putendl_fd("heredoc: Bad trigger.", g_curs.fd);
		ft_strdel(&(g_curs.hd->cmd));
	}
	if (i == 2)
	{
		ft_putstr_fd("21sh: heredoc: Can't acces to tmp directory.\n", g_curs.fd);
		exit(0);
	}
	free(g_curs.hd);
	g_curs.hd = NULL;
}

int				ft_heredoc_addcontent(char *str)
{
	int		fd;
	char	ret;

	ret = '\n';
	fd = -1;
	if (!str)
		str = ft_strdup("");
	if (access("/tmp/.__21sh_tmp_hd", W_OK) == 0)
	{
		fd = open("/tmp/.__21sh_tmp_hd", O_APPEND | O_RDWR);
		if (fd < 0)
			return (0);
		write(fd, str, ft_strlen(str));
		write(fd, &ret, 1);
		close(fd);
		ft_strdel(&g_curs.retval);
		return (1);
	}
	fd = open("/tmp/.__21sh_tmp_hd", O_CREAT | O_WRONLY);
	if (fd < 0)
		return (0);
	write(fd, str, ft_strlen(str));
	close(fd);
	ft_strdel(&g_curs.retval);
	return (1);
}

int				ft_heredoc_exec(char *str)
{
	int		fd;
	pid_t	pid;

	fd = -1;
	if (ft_strcmp(str, g_curs.hd->trigger) == 0)
	{
		pid = fork();
		if (pid > 0)
			wait(&pid);
		else
		{
			if ((fd = open("/tmp/.__21sh_tmp_hd", O_RDONLY)) == -1)
				ft_heredoc_err(2);
			dup2(fd, STDIN_FILENO);
			ms_exec(g_curs.hd->cmd, g_curs.env);
			close(fd);
			exit(0);
		}
		return (1);
	}
	else
		return (0);
}

void			ft_heredoc_proc(void)
{
	if (!g_curs.hd && ft_heredoc_new() > 0)
	{
		ft_strdel(&g_curs.retval);
		ft_putstr_fd("heredoc> ", g_curs.fd);
		return ;
	}
	if (!g_curs.hd)
		return ;
	if ((g_curs.hd && !g_curs.retval) || ft_heredoc_exec(g_curs.retval) == 0)
	{
		ft_heredoc_addcontent(g_curs.retval);
		ft_putstr_fd("heredoc> ", g_curs.fd);
		ft_strdel(&g_curs.retval);
		return ;
	}
	else
		ft_heredoc_del();
	ft_strdel(&g_curs.retval);
}
