/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 14:25:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/29 22:43:43 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ft_redir(char *cmd)
{
	int		i;

	if (ft_cindex(cmd, '>') > 0)
	{
		i = ft_cindex(cmd, '>');
		if (cmd[i + 1] == '>')
			ft_redir_double_right(cmd);
		else if (cmd[i + 1] == '&')
			ft_redir_fd(cmd);
		else
			ft_redir_right(cmd);
	}
	else if (ft_cindex(cmd, '<') > 0)
	{
		i = ft_cindex(cmd, '<');
		if (cmd[i + 1] == '<')
			ft_redir_double_left(cmd);
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

void	ft_redir_double_right(char *cmd)
{
	int		i;
	int		j;
	int		fd;
	char	*filename;
	char	**tmp;

	j = 0;
	i = ft_cindex(cmd, '>');
	filename = (char*)malloc(sizeof(char) * (ft_strlen(cmd) - 1 - i));
	ft_bzero(filename, ft_strlen(cmd) - i);
	while (cmd[++i])
	{
		if (cmd[i] == ' ' || cmd[i] == '	' || cmd[i] == '>')
			continue ;
		filename[j] = cmd[i];
		j++;
	}
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		ft_putendl("21sh: File creation has fails.");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	tmp = ft_strsplit(cmd, '>');
	g_cmd = ms_get_cmd(tmp[0]);
}
