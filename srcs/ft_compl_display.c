/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:20:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/14 13:23:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

size_t			ft_compl_maxlen(t_compl *print)
{
	size_t		maxlen;
	t_compl		*tmp;

	tmp = print;
	maxlen = 0;
	while (tmp)
	{
		if (tmp->len > maxlen)
			maxlen = tmp->len;
		tmp = tmp->next;
	}
	return (maxlen);
}

int			ft_compl_countfile(t_compl *print)
{
	int			nbfile;
	t_compl		*tmp;

	nbfile = 0;
	tmp = print;
	while (tmp)
	{
		nbfile++;
		tmp = tmp->next;
	}
	return (nbfile);
}

void		ft_compl_initdisplay(int maxline)
{
	int		nbret;
	int		i;

	nbret = maxline - (g_curs.ws[1] - g_curs.curs_pos[1]);
	i = nbret;
	if (nbret > 0)
	{
		tputs(tgoto(tgetstr("cm", 0), 0, g_curs.ws[1]), 1, ft_char);
		while (nbret >= 0)
		{
			tputs(tgetstr("do", 0), 1, ft_char);
			g_curs.curs_pos[1] -= 1;
			g_curs.initpos[1] -= 1;
			nbret--;
		}
		while (i-- > 0)
			tputs(tgetstr("up", 0), 1, ft_char);
		ft_init_pos();
		ft_count_chain();
	}
}

void		ft_compl_print(t_compl *print, int maxlen, int maxcol)
{
	int		count;
	t_compl	*tmp;

	maxlen = 0; // A supprimer !!!!!!!!!!!!!!!!!
	maxcol = 0; // A supprimer !!!!!!!!!!!!!!!!!
	tmp = print;
	count = 0;
	tputs(tgetstr("sc", 0), 1, ft_char);
	tputs(tgetstr("do", 0), 1, ft_char);
	while (tmp)
	{
		ft_putstr_fd(print->name, g_curs.fd);
		ft_putchar_fd(' ', g_curs.fd);
	}
	tputs(tgetstr("rc", 0), 1, ft_char);
}

void		ft_compl_display(t_compl *print)
{
	size_t		maxlen;
	int			nbfile;
	int			maxcol;
	int			maxline;

	maxlen = ft_compl_maxlen(print) + 1;
	nbfile = ft_compl_countfile(print);
	maxcol = g_curs.ws[0] / (int)maxlen;
	maxline = nbfile / maxcol;
	ft_compl_initdisplay(maxline);
	ft_compl_print(print, maxlen, maxcol);
}
