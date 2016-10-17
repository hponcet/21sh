/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_getpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 14:37:08 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 15:51:02 by hponcet          ###   ########.fr       */
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
	if (i == 0)							// SI racine
		getroot(ret);
	else if (ret[1][0] == '/' && i > 0)		// SI racine + path
		getpathroot(ret);
	else if (ret[1][0] != '/' && i > 0)
		getpath(ret, pwd);
	else
		ret[0] = ft_strdup(pwd);
	ft_strdel(&pwd);
}