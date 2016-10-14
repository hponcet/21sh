/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:36:51 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/14 13:11:09 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_compl_wis(char *str)
{
	int		i;
	int		j;

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

	while (chain)
	{
		tmp = chain;
		ft_strdel(&(chain->name));
		chain = chain->next;
		free(tmp);
	}
}

void		ft_compl_proc(t_compl *dir, char *find)
{
	t_compl		*print;

	print = ft_compl_makefindchain(dir, find);
	ft_compl_display(print);
}

void		ft_compl_file(char *str)
{
	char	*path;
	char	*find;
	t_compl	*dir;

	dir = NULL;
	path = ft_compl_getpath(str);
	find = ft_compl_getfind(str);
	dir = ft_compl_makechain(path, dir);
	ft_strdel(&path);
	ft_compl_proc(dir, find);
}

char		*ft_compl(char *str)
{
	if (ft_compl_wis(str) == 1)
		ft_compl_file(str);
//	else
//		ft_compl_bin(str);
	return (str);
}