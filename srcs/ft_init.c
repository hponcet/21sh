/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:49:03 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 17:18:15 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		**ft_change_shlvl(char **env)
{
	char	*shlvl;
	char	*ret;
	int		i;

	shlvl = ms_get_value(env, "SHLVL");
	i = ft_atoi(shlvl);
	i++;
	free(shlvl);
	shlvl = ft_itoa(i);
	ret = ft_strjoin("SHLVL=", shlvl);
	ms_builtin_srchnrep(ret, env);
	ft_strdel(&ret);
	ft_strdel(&shlvl);
	return (env);
}

static void	ft_load_2(void)
{
	g_curs.hd = NULL;
	g_curs.tmpchain = NULL;
	g_curs.copy = NULL;
	g_curs.retval = NULL;
	g_curs.history = NULL;
	ft_init_hist();
	ft_window_size();
	g_curs.nb_chr = 0;
	g_curs.id = 1;
	g_curs.next = NULL;
	g_curs.prev = NULL;
}

void		ft_load(int ac, char **av)
{
	get_fd();
	ft_term_init();
	ft_sh_check_opt(ac, av);
	g_curs.curs_pos = (int*)malloc(sizeof(int) * 2);
	g_curs.initpos = (int*)malloc(sizeof(int) * 2);
	g_curs.ws = (int*)malloc(sizeof(int) * 2);
	g_curs.ls = NULL;
	g_curs.select = NULL;
	g_curs.qt = 0;
	ft_cursor_pos();
	ft_put_name();
	g_curs.initpos[0] = g_curs.curs_pos[0];
	g_curs.initpos[1] = g_curs.curs_pos[1];
	g_curs.chain = NULL;
	g_curs.hash_bin = ft_hash_bin();
	ft_load_2();
}

void		ft_init(void)
{
	ft_del_chain();
	g_curs.nb_chr = 0;
	g_curs.id = 1;
	g_curs.prev = NULL;
	g_curs.next = NULL;
	if (g_curs.retval)
	{
		ft_init_hist();
		ft_strdel(&g_curs.retval);
	}
	ft_cursor_pos();
	g_curs.initpos[0] = g_curs.curs_pos[0];
	g_curs.initpos[1] = g_curs.curs_pos[1];
	ft_signal();
}

void		ft_init_window(void)
{
	ft_window_size();
	tputs(tgoto(tgetstr("cl", 0), 1, 0), 1, ft_char);
	ft_put_name();
	g_curs.initpos[1] = 1;
	ft_cursor_pos();
	ft_count_chain();
	ft_init_pos();
}
