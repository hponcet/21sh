/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:36:51 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 02:44:03 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_compl_wis(char *str)
{
	int		i;
	int		j;

	if (!str)
		return (0);
	i = ft_strlen(str) - 1;
	j = 0;
	while (str[j] && (str[j] == ' ' || str[j] == '	'))
		j++;
	if (i == j)
		return (0);
	while (i >= j)
	{
		if (str[i] == ' ' && i > 0 && str[i - 1] != ' ' && str[i - 1] != ';'
				&& str[i - 1] != '`')
			return (1);
		if (str[i] == ';' || str[i] == '`')
			return (0);
		i--;
	}
	return (0);
}

void		ft_compl_delchain(t_compl *chain)
{
	t_compl	*tmp;

	if (chain == chain->next)
	{
		ft_strdel(&(chain->name));
		free(chain);
		return ;
	}
	while (chain)
	{
		tmp = chain;
		ft_strdel(&(chain->name));
		chain = chain->next;
		tmp = NULL;
	}
}

void		ft_compl_file(char *str)
{
	char	*path;
	char	*find;
	t_compl	*dir;
	int		i;

	dir = NULL;
	path = ft_compl_getpath();
	find = ft_compl_getfind(str);
	if (!find)
		find = ft_strnew(0);
	i = ft_strlen(find) - 1;
	if (i >= 0 && find[i] == '/')
	{
		path = ft_joinf("%xs/%xs", path, find);
		find = ft_strnew(0);
	}
	dir = ft_compl_makechain(path, dir, find);
	if (dir)
		ft_compl_display(dir, find);
	ft_strdel(&path);
	ft_strdel(&find);
}

char		*ft_compl(char *str)
{
	if (ft_compl_wis(str) == 1)
		ft_compl_file(str);
//	else
//		ft_compl_bin(str);
	return (str);
}
