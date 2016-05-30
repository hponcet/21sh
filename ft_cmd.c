/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:55:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/28 15:56:01 by hponcet          ###   ########.fr       */
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
		ms_exec(cmd[i], g_env);
		g_moddedenv = 0;
		i++;
	}
}
