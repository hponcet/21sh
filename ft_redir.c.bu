/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 14:25:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/16 01:24:29 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ft_redir(char *cmd)
{
	int		i;
	char	*cpcmd;

	cpcmd = ft_strdup(cmd);
	if (ft_cindex(cmd, '>') > 0)
	{
		i = ft_cindex(cmd, '>');
		if (cmd[i + 1] == '>')
			ft_redir_recurs_double_right(cpcmd);
		else if (cmd[i + 1] == '&')
			ft_redir_fd(cmd);
		else
			ft_redir_recurs_right(cpcmd);
	}
	else if ((i = ft_cindex(cmd, '<') > 0) && cmd[i + 1] != '<')
	{
		if (cmd[i + 1] == '&')
			ft_redir_fd_left(cmd);
		else
			ft_redir_left(cmd);
	}
}

void	ft_redir_left(char *cmd)
{
	int		i;
	int		fd;
	char	*filename;
	char	**tmp;

	i = ft_cindex(cmd, '<') + 1;
	while (cmd[i] == ' ' || cmd[i] == '	')
		i++;
	filename = ft_strsub(cmd, i, ft_strlen(cmd) - i);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_printf("21sh: %s: Bad file name or can't access.\n", filename);
		exit(0);
	}
	dup2(fd, STDIN_FILENO);
	tmp = ft_strsplit(cmd, '<');
	g_cmd = ms_get_cmd(tmp[0]);
	ms_free_tab(tmp);
}
