/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:55:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/09 15:27:01 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ft_cmd(char *enter)
{
	char	**cmd;
	int		i;

	enter = ft_bquote(enter);
	cmd = ft_cmd_split(enter);
	ft_putendl("--------------------");
	ms_print_env(cmd);
	ft_putendl("--------------------");
	i = 0;
	while (cmd[i])
	{
		ms_exec(cmd[i], g_env);
		g_moddedenv = 0;
		i++;
	}
	ms_free_tab(cmd);
}
