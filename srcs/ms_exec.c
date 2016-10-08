/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 07:24:49 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/08 05:17:46 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void		ms_exec(char *cmd, char **env)
{
	int		pid;

	g_cmd = ms_get_cmd(cmd);
	if (ft_cindex(cmd, '|') == -1)
	{
		env = ms_builtin_cd(env);
		if (g_cmd)
			env = ms_search_builtin_env(cmd, env);
		if (g_cmd && g_cmd[0][0] == '.' && ms_get_point() < 1)
			return ;
		if (g_i == 0)
			ms_exec_fork(cmd, env);
		g_i = 0;
	}
	else
	{
		pid = fork();
		if (pid > 0)
			wait(&pid);
		else
			ft_ast(cmd);
	}
	if (g_cmd)
		ft_tabdel(g_cmd);
	g_cmd = NULL;
}

void		ms_exec_fork(char *cmd, char **env)
{
	pid_t	pid;

	if (!g_cmd)
		return ;
	pid = fork();
	if (pid > 0)
		wait(&pid);
	else
	{
		if (cmd && (ft_cindex_noquote(cmd, '>') > 0 ||
					ft_cindex_noquote(cmd, '<') > 0))
			ft_redir(cmd);
		ms_exec_bin(ms_search_bin(env), env);
		exit(0);
	}
}

void		ms_exec_bin(char *pathbin, char **env)
{
	if (!pathbin)
		exit(0);
	execve(pathbin, g_cmd, env);
	g_cmd = ms_free_tab(g_cmd);
}
