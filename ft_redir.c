/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 14:25:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/03 20:28:37 by hponcet          ###   ########.fr       */
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
	free(cpcmd);
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
}

void	ft_redir_recurs_right(char *cmd)
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
		free(tmp);
		free(join);
		ft_redir_right(ncmd);
		free(ncmd);
		tmp = cmd;
		cmd = ft_strsub(cmd, 0, j);
		free(tmp);
		i = ft_cindex(cmd, '>');
		j = ft_cindex_rev(cmd, '>');
	}
	ft_redir_right(cmd);
}

void	ft_redir_right(char *cmd)
{
	int		i;
	int		j;
	int		fd;
	char	*filename;
	char	**tmp;

	j = 0;
	i = ft_cindex(cmd, '>');
	filename = (char*)malloc(sizeof(char) * (ft_strlen(cmd) - i));
	ft_bzero(filename, ft_strlen(cmd) - i);
	while (cmd[++i])
	{
		if (cmd[i] == ' ' || cmd[i] == '	')
			continue ;
		filename[j] = cmd[i];
		j++;
	}
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		ft_putendl("21sh: File creation has fails.\n");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	tmp = ft_strsplit(cmd, '>');
	g_cmd = ms_get_cmd(tmp[0]);
}
