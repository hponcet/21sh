/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 19:48:20 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/15 14:09:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_catch_signal(int signo)
{
	if (signo == SIGWINCH)
		ft_init_window();
	if (signo == SIGINT)
		ft_init_prompt();
}

void		ft_signal(void)
{
	signal(SIGWINCH, ft_catch_signal);
	signal(SIGINT, ft_catch_signal);
}

void		ft_init_prompt(void)
{
	ft_heredoc_del();
	ft_putendl("");
	ft_put_name();
	ft_init();
}

static void	ft_signal_exit(void)
{
	signal(SIGINT, SIG_DFL);
	ft_putendl("");
}

static void	ft_catch_signal_onexec(int signo)
{
	if (signo == SIGINT)
		ft_signal_exit();
}

void		ft_signal_onexec(void)
{
	signal(SIGINT, ft_catch_signal_onexec);
}
