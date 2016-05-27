/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:55:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/27 13:59:46 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

void	ft_cmd(void)
{
	char	**cmd;
	int		i;

	cmd = ft_strsplit(g_retval, ';');
	i = 0;
	while (cmd[i])
	{
		if (ft_cindex(cmd[i], '|') > 0)
			ft_ast(cmd[i]);
		else
		{
			g_cmd = ms_get_cmd(cmd[i]);
			ms_exec(g_env);
			g_moddedenv = 0;
		}
		i++;
	}
}
