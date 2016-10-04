/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:55:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 14:02:58 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ft_cmd(char *enter)
{
	char	**cmd;
	int		i;

	if (ft_cindex(enter, '$') >= 0)
		enter = ft_dollar(enter);
	cmd = ft_cmd_split(enter);
	i = 0;
	while (cmd[i])
	{
		ms_exec(cmd[i], g_curs.env);
		g_moddedenv = 0;
		i++;
	}
	ms_free_tab(cmd);
}
