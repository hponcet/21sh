/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_opt_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 15:47:01 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/18 15:10:06 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_func_copy(char *buf)
{

	if (buf[0] == -30 && buf[1] == -119 && buf[2] == -92 && buf[3] == 0)
	{
		ft_copy();
		ft_reset_select();
	}
	if (buf[0] == -30 && buf[1] == -119 && buf[2] == -91 && buf[3] == 0)
		ft_paste();
}

void		ft_copy(void)
{
	t_chain		*tmp;
	size_t		i;

	if (g_curs.select == NULL)
		return ;
	i = 0;
	tmp = g_curs.select;
	while (tmp && tmp->sel == 1)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = g_curs.select;
	if (g_copy)
		free(g_copy);
	g_copy = (char*)malloc(sizeof(char) * (i + 1));
	ft_bzero(g_copy, i + 1);
	i = 0;
	while (tmp && tmp->sel == 1)
	{
		g_copy[i] = tmp->c;
		i++;
		tmp = tmp->next;
	}
	ft_count_chain();
}

void		ft_paste(void)
{
	int		i;

	if(!g_copy)
		return ;
	i = 0;
	if (!g_copy)
		return ;
	while (g_copy[i])
	{
		ft_chain_addchar(g_copy[i]);
		i++;
	}
}
