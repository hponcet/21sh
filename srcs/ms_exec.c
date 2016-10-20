/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 07:24:49 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 01:49:45 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void		ms_exec(char *cmd, char **env)
{
	env = ms_builtin_cd(env);
	if (g_cmd)
		env = ms_search_builtin_env(cmd, env);
	if (g_cmd && g_cmd[0][0] == '.' && ms_get_point() < 1)
		return ;
	if (g_i == 0)
		ms_exec_fork(cmd, env);
	g_i = 0;
	if (g_cmd)
		ft_tabdel(g_cmd);
	g_cmd = NULL;
}

void		ms_exec_fork(char *cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!g_cmd)
		return ;
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		if (ft_cindex_noquote(cmd, '|') > 1)
			ft_ast(cmd);
		ft_redir_exec(cmd);
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
