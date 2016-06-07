/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 12:12:26 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/06 21:25:28 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char		*ft_isbq(char *cmd)
{
	int		i;
	int		ci;
	char	*tmp;
	char	*ret;

	ci = 0;
	i = 0;
	tmp = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '`')
		{
			tmp = cmd + i + 1;
			if ((ci = ft_cindex(tmp, '`')) < 0)
				return (NULL);
			ret = ft_strsub(tmp, 0, ci);
			return (ret);
		}
		if (cmd[i] == 92)
			i++;
		i++;
	}
	return (NULL);
}

static char		*ft_bquote_exec(char *cmd)
{
	pid_t	pid;
	char	buf[256];
	char	*ret;
	int		fd[2];

	ret = ft_strnew(0);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		ms_exec(cmd, g_env);
		exit(0);
	}
	else
	{
		close(fd[1]);
		while (read(fd[0], buf, 255) > 0)
		{
			ret = ft_joinf("%xs%s", ret, buf);
			ft_bzero(buf, 256);
		}
		wait(&pid);
	}
	return (ret);
}

static char		*ft_bquote_join(char *ret, char *cmd, char *retsub)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '`')
		{
			i++;
			while (cmd[i] != '`')
				i++;
			i++;
			while (retsub[++k])
				ret[++j] = (retsub[k] == '\n') ? ' ' : retsub[k];
		}
		ret[++j] = cmd[i];
	}
	return (ret);
}

char			*ft_bquote(char *cmd)
{
	char		*subcmd;
	char		*retsubcmd;
	char		*ret;
	int			nlen;

	if (!(subcmd = ft_isbq(cmd)))
		return (cmd);
	retsubcmd = ft_bquote_exec(subcmd);
	nlen = ft_strlen(cmd) - (ft_strlen(subcmd) + 2) + ft_strlen(retsubcmd) + 1;
	ret = (char*)malloc(sizeof(char) * nlen);
	ft_bzero(ret, nlen);
	ret = ft_bquote_join(ret, cmd, retsubcmd);
	ft_strdel(&subcmd);
	ft_strdel(&retsubcmd);
	return (ret);
}
