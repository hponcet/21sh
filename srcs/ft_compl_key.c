/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 20:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 02:45:13 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_compl_addstr(char *str, int type)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_chain_addchar(str[i++]);
		ft_init_pos();
		ft_count_chain();
	}
	if (type == 1)
		ft_chain_addchar('/');
	else if (type == 0)
		ft_chain_addchar(' ');
}

static int	ft_compl_retstr(t_compl *tmp, char *find, int x, int y, int ret)
{
	tputs(tgoto(tgetstr("cm", 0), x - 1, y - 1), 1, ft_char);
	tputs(tgetstr("ce", 0), 1, ft_char);
	ft_compl_addstr(tmp->name + ft_strlen(find), tmp->type);
	return (ret);
}

int			ft_compl_key(char *buf, t_compl **print, char *find, int x, int y)
{
	t_compl		*tmp;

	tmp = print[0];
	if (buf[0] == 10)
		return (ft_compl_retstr(tmp, find, x, y, 1));
	else if (buf[0] == 9 && buf[1] == 0)
	{
		if (tmp == tmp->next)
			return (ft_compl_retstr(tmp, find, x, y, 1));
		tmp = tmp->next;
	}
	else if (ft_isprint(buf[0]) == 1 && buf[1] == 0)
		return (ft_compl_retstr(tmp, find, x, y, 1));
	else if (buf[0] == 127 && buf[1] == 0 && g_curs.chain)
		return (ft_compl_retstr(tmp, find, x, y, 1));
	else if (buf[0] == 27)
		return (ft_compl_retstr(tmp, find, x, y, 1));
	tputs(tgoto(tgetstr("cm", 0), x - 1, y - 1), 1, ft_char);
	ft_putstr(tmp->name + ft_strlen(find));
	tputs(tgetstr("ce", 0), 1, ft_char);
	*print = tmp;
	return (0);
}
