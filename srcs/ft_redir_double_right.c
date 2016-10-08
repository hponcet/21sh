/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_double_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:08:37 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/08 02:02:39 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void			ft_redir_recurs_double_right(char *cmd)
{
	int		i;
	int		j;
	char	*ncmd;
	char	*tmp;
	char	*join;

	i = ft_cindex_noquote(cmd, '>');
	j = ft_cindex_noquote_rev(cmd, '>') - 1;
	while (i != j)
	{
		ncmd = ft_strsub(cmd, 0, i + 1);
		tmp = ncmd;
		join = ft_strsub(cmd, j + 2, ft_strlen(cmd) - j - 1);
		ncmd = ft_strjoin(ncmd, join);
		free(tmp);
		free(join);
		ft_redir_right(ncmd);
		free(ncmd);
		cmd = ft_strsub(cmd, 0, j);
		i = ft_cindex_noquote(cmd, '>');
		j = ft_cindex_noquote_rev(cmd, '>') - 1;
	}
	ft_redir_double_right(cmd);
}

static int		ft_redir_fdout(char *cmd)
{
	int		i;
	int		j;
	char	*fdout;

	j = 0;
	i = ft_cindex_noquote(cmd, '>');
	if (i >= 1 && ft_isdigit(cmd[i - 1]) == 0)
		return (STDOUT_FILENO);
	while (i >= 1 && cmd[i - 1] >= 48 && cmd[i - 1] <= 57)
	{
		i--;
		j++;
	}
	fdout = ft_strsub(cmd, i, j);
	return (ft_atoi(fdout));
}

void			ft_redir_double_right(char *cmd)
{
	int		t[4];
	char	*filename;

	t[1] = 0;
	t[0] = ft_cindex_noquote(cmd, '>');
	t[3] = ft_redir_fdout(cmd);
	filename = ft_strnew(ft_strlen(cmd) - t[0]);
	while (cmd[++t[0]])
	{
		if (cmd[t[0]] == ' ' || cmd[t[0]] == '	' || cmd[t[0]] == '>')
			continue ;
		filename[t[1]] = cmd[t[0]];
		t[1]++;
	}
	if ((t[2] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		return (ft_putendl("21sh: File creation has fails."));
	dup2(t[2], t[3]);
	t[0] = ft_cindex_noquote(cmd, '>') - 1;
	while (cmd[t[0]] >= '0' && cmd[t[0]] >= '9')
		t[0]--;
	ft_strdel(&filename);
	filename = ft_strsub(cmd, 0, t[0]);
	g_cmd = ms_parse_cmd(filename);
}
