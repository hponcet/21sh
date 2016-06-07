/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 07:24:49 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/06 21:27:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"



void		ms_exec(char *cmd, char **env)
{
	pid_t pid;

	g_cmd = ms_get_cmd(cmd);
	if (ft_cindex(cmd, '|') == -1)
	{
		env = ms_builtin_cd(env);
		if (g_cmd)
			env = ms_search_builtin_env(cmd, env);
		if (g_cmd && g_cmd[0][0] == '.')
			if (ms_get_point() < 1)
				return ;
		ms_exec_fork(cmd, env);
	}
	else
	{
		pid = fork();
		if (pid > 0)
			wait(&pid);
		else
			ft_ast(cmd);
	}
	free(g_cmd);
}

void	ms_exec_fork(char *cmd, char **env)
{
	pid_t	pid;

	if (!g_cmd)
		return ;
	pid = fork();
	if (pid > 0)
		wait(&pid);
	else
	{
		if (ft_cindex(cmd, '>') > 0 || ft_cindex(cmd, '<') > 0)
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
	if (g_moddedenv > 0)
	{
		if (g_i == 0)
			env = ms_free_tab(env);
		g_i = 0;
		g_moddedenv = 0;
	}
}
