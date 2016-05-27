/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:55:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/27 10:21:32 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

void	ft_cmd(void)
{
	char	**cmd;
	int		i;
	pid_t	pid;

	cmd = ft_strsplit(g_retval, ';');
	i = 0;
	while (cmd[i])
	{
		pid = fork();
		if (pid > 0)
			wait(NULL);
		else
		{
			if (ft_cindex(cmd[i], '|') > 0)
				ft_ast(cmd[i]);
			else
			{
				g_cmd = ms_get_cmd(cmd[i]);
				ms_exec(g_env);
				g_moddedenv = 0;
			}
		}
		i++;
	}
}
