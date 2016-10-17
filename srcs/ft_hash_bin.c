/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 21:45:34 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 00:00:29 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_hash		**ft_hash_bin(void)
{
	t_hash	**htbl;
	char	**paths;
	int		i;

	i = 0;
	htbl = ft_hash_newtbl(__HTBL_LEN__);
	paths = ms_search_paths();
	while (paths[i])
	{
		ft_hash_addpath(htbl, paths[i], __HTBL_LEN__);
		i++;
	}
	ft_tabdel(paths);
	return (htbl);
}
