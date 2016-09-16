/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 22:44:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/16 15:19:59 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void		ft_heredoc_err(int i)
{
	if (i == 0)
		ft_putendl_fd("heredoc: Bad command.", g_fd);
	if (i == 1)
	{
		ft_putendl_fd("heredoc: Bad trigger.", g_fd);
		ft_strdel(&(g_hd->cmd));
	}
	if (i == 2)
	{
		ft_putstr_fd("21sh: heredoc: Can't acces to tmp directory.\n", g_fd);
		exit(0);
	}
	free(g_hd);
	g_hd = NULL;
}

int				ft_heredoc_new(void)
{
	int		i;

	g_hd = (t_hd*)malloc(sizeof(t_hd));
	i = ft_heredoc_check();
	while ((g_retval[i] == ' ' || g_retval[i] == '	' || g_retval[i] == '<')
			&& i >= 0)
		i--;
	if (i == 0)
	{
		ft_heredoc_err(0);
		return (0);
	}
	g_hd->cmd = ft_strsub(g_retval, 0, i + 1);
	i = ft_heredoc_check();
	while (g_retval[i] == ' ' || g_retval[i] == '	' || g_retval[i] == '<')
		i++;
	if (g_retval[i] == '\0')
	{
		ft_heredoc_err(1);
		return (0);
	}
	g_hd->trigger = ft_strsub(g_retval, i, ft_strlen(g_retval) - i);
	ft_hist_addtohist(g_retval);
	ft_strdel(&g_retval);
	return (1);
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
		ft_strdel(&g_retval);
		return (1);
	}
	fd = open("/tmp/.__21sh_tmp_hd", O_CREAT | O_WRONLY);
	if (fd < 0)
		return (0);
	write(fd, &str, ft_strlen(str));
	close(fd);
	ft_strdel(&g_retval);
	return (1);
}

int				ft_heredoc_exec(char *str)
{
	int		fd;
	pid_t	pid;

	fd = -1;
	if (ft_strcmp(str, g_hd->trigger) == 0)
	{
		pid = fork();
		if (pid > 0)
			wait(&pid);
		else
		{
			if ((fd = open("/tmp/.__21sh_tmp_hd", O_RDONLY)) == -1)
				ft_heredoc_err(2);
			dup2(fd, STDIN_FILENO);
			ms_exec(g_hd->cmd, g_env);
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
	if (!g_hd && ft_heredoc_new() > 0)
	{
		ft_strdel(&g_retval);
		ft_putstr_fd("heredoc> ", g_fd);
		return ;
	}
	if (!g_hd)
		return ;
	if ((g_hd && !g_retval) || ft_heredoc_exec(g_retval) == 0)
	{
		ft_heredoc_addcontent(g_retval);
		ft_putstr_fd("heredoc> ", g_fd);
		ft_strdel(&g_retval);
		return ;
	}
	else
		ft_heredoc_del();
	ft_strdel(&g_retval);
}
