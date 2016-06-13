/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_simple_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 17:56:46 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/13 20:31:54 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static char	*ft_redir_right_getfilename(char *cmd)
{
	char	*filename;
	int		i;
	int		j;

	i = ft_cindex(cmd, '>');
	j = 0;
	filename = ft_strnew(ft_strlen(cmd) - i);
	ft_bzero(filename, ft_strlen(cmd) - i);
	while (cmd[++i])
	{
		if (cmd[i] == ' ' || cmd[i] == '	')
			continue ;
		filename[j] = cmd[i];
		j++;
	}
	return (filename);
}

static int	ft_redir_right_getfd(char *cmd)
{
	int		i;
	int		j;
	char	fd[256];

	ft_bzero(fd, 256);
	i = ft_cindex(cmd, '>') - 1;
	j = 0;
	while (ft_isdigit(cmd[i]) == 1)
	{
		fd[j] = cmd[i];
		i++;
		j++;
	}
	j = ft_atoi(fd);
	return (j);
}

void		ft_redir_recurs_right(char *cmd)
{
	int		i;
	int		j;
	char	*ncmd;
	char	*tmp;
	char	*join;
	
	i = ft_cindex(cmd, '>');
	j = ft_cindex_rev(cmd, '>');
	while (i != j)
	{
		ncmd = ft_strsub(cmd, 0, i + 1);
		tmp = ncmd;
		join = ft_strsub(cmd, j + 1, ft_strlen(cmd) - j);
		ncmd = ft_strjoin(ncmd, join);
		ft_strdel(&tmp);
		ft_strdel(&join);
		ft_redir_right(ncmd);
		ft_strdel(&ncmd);
		tmp = cmd;
		cmd = ft_strsub(cmd, 0, j);
		ft_strdel(&tmp);
		i = ft_cindex(cmd, '>');
		j = ft_cindex_rev(cmd, '>');
	}
	ft_redir_right(cmd);
}

void		ft_redir_right(char *cmd)
{
	int		fd;
	int		fdout;
	char	*filename;
	char	*tmpcmd;
	int		i;

	fdout = 1;
	i = ft_cindex(cmd, '>');
	filename = ft_redir_right_getfilename(cmd);
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		ft_putendl("21sh: File creation has fails.\n");
		return ;
	}
	if (i > 0 && ft_isdigit(cmd[i - 1]) == 1)
		fdout = ft_redir_right_getfd(cmd);
	dup2(fd, fdout);
	while (--i > 0 && ft_isdigit(cmd[i]) == 1)
		;
	tmpcmd = ft_strsub(cmd, 0, i);
	g_cmd = ms_get_cmd(tmpcmd);
	ft_strdel(&tmpcmd);
}
