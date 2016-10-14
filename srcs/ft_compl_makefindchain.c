/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_makefindchain.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:01:04 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/14 13:16:02 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_compl_copyfile(t_compl *findlist, t_compl *orig)
{
	t_compl	*file;

	file = (t_compl*)malloc(sizeof(t_compl));
	if (!file)
		return ;
	file->name = ft_strdup(orig->name);
	file->len = orig->len;
	file->type = orig->type;
	file->x = 0;
	file->y = 0;
	file->next = NULL;
	ft_compl_sortchain(&findlist, file);
}

t_compl		*ft_compl_makefindchain(t_compl *dir, char *find)
{
	t_compl		*findlist;
	t_compl		*tmp;
	int			len;

	len = ft_strlen(find);
	findlist = NULL;
	tmp = dir;
	while (tmp)
	{
		if (ft_strncmp(find, tmp->name, len) == 0)
			ft_compl_copyfile(findlist, tmp);
		tmp = tmp->next;
	}
	ft_compl_delchain(dir);
	return (findlist);
}
