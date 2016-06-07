/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_double_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:08:37 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/03 20:35:26 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ft_redir_recurs_double_right(char *cmd)
{
	int		i;
	int		j;
	char	*ncmd;
	char	*tmp;
	char	*join;
	
	i = ft_cindex(cmd, '>');
	j = ft_cindex_rev(cmd, '>') - 1;
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
		i = ft_cindex(cmd, '>');
		j = ft_cindex_rev(cmd, '>') - 1;
	}
	ft_redir_double_right(cmd);
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
	filename = (char*)malloc(sizeof(char) * (ft_strlen(cmd) - i));
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
