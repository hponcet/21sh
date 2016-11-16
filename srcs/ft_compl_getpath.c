/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_getpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 14:37:08 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/16 17:24:27 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	getroot(char **ret)
{
	int		len;
	char	*tmp;

	if (ret[1][1])
	{
		len = ft_strlen(ret[1]) - 1;
		tmp = ft_strsub(ret[1], 1, len);
		free(ret[1]);
		ret[1] = tmp;
		ret[0] = ft_strdup("/");
	}
	else
	{
		ft_strdel(&ret[1]);
		ret[0] = ft_strdup("/");
	}
}

static void	getpathroot(char **ret)
{
	int		i;
	char	*tmp;

	i = ft_cindex_rev(ret[1], '/');
	if (ret[1][i + 1])
	{
		tmp = ft_strsub(ret[1], i + 1, ft_strlen(ret[1]) - i);
		ret[0] = ft_strsub(ret[1], 0, i + 1);
		free(ret[1]);
		ret[1] = tmp;
	}
	else
	{
		ret[0] = ft_strdup(ret[1]);
		free(ret[1]);
		ret[1] = ft_strnew(0);
	}
}

static void	getpath(char **ret, char *pwd)
{
	int		i;
	char	*path;
	char	*find;

	i = ft_cindex_rev(ret[1], '/');
	find = ft_strsub(ret[1], i + 1, ft_strlen(ret[1]) - i);
	path = ft_strsub(ret[1], 0, i + 1);
	ret[0] = ft_joinf("%s/%s", pwd, path);
	ft_strdel(&path);
	free(ret[1]);
	ret[1] = find;
}

static void gethomepath(char **cmd)
{
	char	*tmp;
	char	*homepath;
	char	*find;
	int		i;

	if (!(homepath = ms_get_value(g_curs.env, "HOME")))
		homepath = ft_strdup("/Users/");
	i = ft_cindex_rev(cmd[1], '/');
	find = ft_strsub(cmd[1], i + 1, ft_strlen(cmd[1]) - i);
	tmp = ft_strsub(cmd[1], 1, i);
	free(cmd[1]);
	cmd[0] = ft_joinf("%s/%s/", homepath, tmp);
	cmd[1] = find;
	ft_strdel(&tmp);
	ft_strdel(&homepath);
}

void		ft_compl_getpath(char **ret)
{
	char	*pwd;
	int		i;

	pwd = NULL;
	pwd = getcwd(pwd, MAXPATHLEN);
	if (!ret[1])
	{
		ret[1] = ft_strnew(0);
		ret[0] = ft_strdup(pwd);
		ft_strdel(&pwd);
		return ;
	}
	i = ft_cindex_rev(ret[1], '/');
	if (ret[1][0] == '~' && ret[1][1] == '/')
		gethomepath(ret);
	else if (i == 0)
		getroot(ret);
	else if (ret[1][0] == '/' && i > 0)
		getpathroot(ret);
	else if (ret[1][0] != '/' && i > 0)
		getpath(ret, pwd);
	else
		ret[0] = ft_strdup(pwd);
	ft_strdel(&pwd);
}
