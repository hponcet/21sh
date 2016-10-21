/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 20:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 18:45:54 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_compl_addstrend(char *str, int type)
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

static void	ft_compl_addstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_chain_addchar(str[i++]);
		ft_init_pos();
		ft_count_chain();
	}
}

static int	ft_compl_retstr(t_compl *tmp, char *find, int *pos, int i)
{
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	tputs(tgetstr("ce", 0), 1, ft_char);
	if (i == 1)
		ft_compl_addstrend(tmp->name + ft_strlen(find), tmp->type);
	else
		ft_compl_addstr(tmp->name + ft_strlen(find));
	return (1);
}

static int	ft_compl_retstrchar(t_compl *tmp, char *find, int *pos, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = tmp->name + ft_strlen(find);
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	tputs(tgetstr("ce", 0), 1, ft_char);
	ft_compl_addstr(str);
	ft_chain_addchar(c);
	ft_init_pos();
	ft_count_chain();
	return (1);
}

int			ft_compl_key(char *buf, t_compl **print, char *find, int *pos)
{
	t_compl		*tmp;

	tmp = print[0];
	if (tmp->next == tmp)
		return (ft_compl_retstr(tmp, find, pos, 1));
	if (buf[0] == 10)
		return (ft_compl_retstr(tmp, find, pos, 1));
	else if (buf[0] == 9 && buf[1] == 0)
	{
		if (tmp == tmp->next)
			return (ft_compl_retstr(tmp, find, pos, 0));
		tmp = tmp->next;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		tmp = tmp->prev;
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		tmp = tmp->next;
	else if (ft_isprint(buf[0]) == 1 && buf[1] == 0)
		return (ft_compl_retstrchar(tmp, find, pos, buf[0]));
	else if (buf[0] == 127 && buf[1] == 0)
		return (ft_compl_retstr(tmp, find, pos, 0));
	else if (buf[0] == 27 && buf[1] == 0)
		return (ft_compl_retstr(tmp, find, pos, 1));
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	ft_putstr(tmp->name + ft_strlen(find));
	tputs(tgetstr("ce", 0), 1, ft_char);
	*print = tmp;
	return (0);
}
