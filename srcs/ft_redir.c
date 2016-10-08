/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 14:25:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/08 02:01:49 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int		ft_cindex_noquote(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == 96)
			i += ft_cmd_count_quote(str, i, str[i]);
		i++;
	}
	if (str[i] != c)
		return (-1);
	return (i);
}


int		ft_cindex_noquote_rev(char *str, char c)
{
	int		len;

	if (!str)
		return (-1);
	len = ft_strlen(str) - 1;
	while (len > -1 && str[len] != c)
	{
		if (str[len] == '\"' || str[len] == '\'' || str[len] == 96)
			len -= ft_cmd_count_quote_rev(str, len, str[len]);
		len--;
	}
	return (len);
}

void			ft_redir(char *cmd)
{
	int		i;
	char	*cpcmd;

	cpcmd = ft_strdup(cmd);
	if (ft_cindex_noquote(cmd, '>') > 0)
	{
		i = ft_cindex_noquote(cmd, '>');
		if (cmd[i + 1] == '>')
			ft_redir_recurs_double_right(cpcmd);
		else if (cmd[i + 1] == '&')
			ft_redir_fd(cmd);
		else
			ft_redir_recurs_right(cpcmd);
	}
	else if ((i = ft_cindex_noquote(cmd, '<') > 0) && cmd[i + 1] != '<')
	{
		if (cmd[i + 1] == '&')
			ft_redir_fd_left(cmd);
		else
			ft_redir_left(cmd);
	}
}

void			ft_redir_left(char *cmd)
{
	int		i;
	int		fd;
	char	*filename;
	char	**tmp;

	i = ft_cindex_noquote(cmd, '<') + 1;
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
	g_cmd = ms_parse_cmd(tmp[0]);
	ms_free_tab(tmp);
}
