/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 02:46:43 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/08 17:10:13 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void		ft_hist_addtofile(char *homepath)
{
	int		fd;
	char	ret;
	t_hist	*tmp;

	ret = '\n';
	fd = open(homepath, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return ;
	if (!g_hist)
	{
		close(fd);
		return ;
	}
	while (g_hist)
	{
		write(fd, g_hist->cmd, ft_strlen(g_hist->cmd));
		write(fd, &ret, 1);
		tmp = g_hist;
		g_hist = g_hist->prev;
		free(tmp->cmd);
		free(tmp);
	}
	close(fd);
}

static void		ft_hist_makechain(char *homepath)
{
	int		fd;
	char	*buf;
	t_hist	*new;
	t_hist	*tmp;

	tmp = NULL;
	new = NULL;
	fd = open(homepath, O_RDONLY, 0644);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &buf) > 0)
	{
		new = (t_hist*)malloc(sizeof(t_hist));
		new->next = tmp;;
		if (tmp)
			tmp->prev = new;
		new->prev = NULL;
		new->cmd = ft_strdup(buf);
		if (!g_hist)
			g_hist = new;
		tmp = new;
		free(buf);
		buf = NULL;
	}
	close(fd);
}

void			ft_init_hist(void)
{
	char	*homepath;

	homepath = ft_strjoin(getenv("HOME"), "/.21history");
	if (g_hist)
		while (g_hist->next)
			g_hist = g_hist->next;
	ft_hist_addtofile(homepath);
	ft_hist_makechain(homepath);
	free(homepath);
}

void			ft_hist_addtohist(char *ncmd)
{
	t_hist	*tmp;

	if (g_hist && ft_strcmp(ncmd, g_hist->cmd) == 0)
		return ;
	tmp = (t_hist*)malloc(sizeof(t_hist));
	tmp->prev = g_hist;
	tmp->next = NULL;
	tmp->cmd = ft_strdup(ncmd);
	if (g_hist)
		g_hist->next = tmp;
	g_hist = tmp;
}

void			ft_histtochain(void)
{
	int		i;

	i = 0;
	if (g_chain)
		ft_del_chain();
	tputs(tgoto(tgetstr("cm", 0), g_initpos[0] - 1, g_initpos[1] - 1), 1, ft_char);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	g_curs.id = 1;
	g_curs.prev = NULL;
	g_curs.next = NULL;
	free(g_retval);
	g_retval = NULL;
	ft_cursor_pos();
	g_initpos[0] = g_curs.curs_pos[0];
	g_initpos[1] = g_curs.curs_pos[1];
	while (g_hist->cmd[i])
	{
		ft_chain_addchar(g_hist->cmd[i]);
		ft_count_chain();
		i++;
	}
	g_curs.hist = 0;
	ft_init_hist();
}
