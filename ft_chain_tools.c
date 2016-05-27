/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chain_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 07:52:25 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/21 15:05:12 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			ft_init_pos(void)
{
	t_chain	*tmp;
	int		h;
	int		v;

	if (!(tmp = g_chain))
		return ;
	h = g_initpos[0];
	v = g_initpos[1];
	while (tmp)
	{
		if (h == g_curs.ws[0] + 1)
		{
			h = 1;
			v += 1;
		}
		tmp->cp[0] = h;
		tmp->cp[1] = v;
		h++;
		g_curs.ls = tmp;
		if (tmp->next)
			tmp = tmp->next;
		else
			break;
	}
	g_curs.ls = tmp;
}

int				ft_count_chain(void)
{
	int		i;
	t_chain	*tmp;

	if (!g_chain)
		return (0);
	i = 1;
	tmp = g_chain;
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
	g_curs.nb_chr = i - 1;
	ft_find_word();
	ft_make_retval();
	return (i);
}

void			ft_find_word(void)
{
	t_chain	*tmp;

	if (!g_chain)
		return ;
	tmp = g_chain;
	while (tmp)
	{
		if (tmp->next && (tmp->c == ' ' || tmp->c == '	') &&
				tmp->next->c != ' ' && tmp->next->c != '	' )
			tmp->next->word = 1;
		tmp = tmp->next;
	}
}

void			ft_make_retval(void)
{
	size_t	i;
	t_chain	*tmp;

	i = 0;
	if (!g_chain)
		return ;
	tmp = g_chain;
	free(g_retval);
	g_retval = NULL;
	g_retval = (char*)malloc(sizeof(char) * g_curs.nb_chr + 2);
	ft_bzero(g_retval, g_curs.nb_chr + 2);
	while (i < g_curs.nb_chr)
	{
		g_retval[i] = tmp->c;
		i++;
		tmp = tmp->next;
	}
}

void			ft_del_chain(void)
{
	t_chain		*tmp;

	if (!g_chain)
		return ;
	while (g_chain)
	{
		tmp = g_chain;
		g_chain = g_chain->next;
		free(tmp->cp);
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
	g_chain = NULL;
	g_retval = NULL;
}
