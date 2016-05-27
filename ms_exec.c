/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 07:24:49 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/27 15:35:51 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void		ms_exec(char **env)
{
	if (!g_cmd[0])
		return ;
	if (g_cmd && g_cmd[0][0] == '.')
		if (ms_get_point() < 1)
			return ;
	env = ms_builtin_cd(env);
	if (g_cmd)
		env = ms_search_builtin_env(env);
	if (!g_cmd)
		return ;
	ms_exec_bin(ms_search_bin(env), env);
}

char		**ms_search_builtin_env(char **env)
{
	if (ft_strcmp(g_cmd[0], "env") == 0)
	{
		if (g_moddedenv == 0)
			env = ms_get_env(g_env);
		g_moddedenv += 1;
		ms_builtin_env(env);
	}
	else if (ft_strcmp(g_cmd[0], "setenv") == 0)
	{
		if (g_moddedenv == 1)
			env = ms_builtin_setenv(env);
		else
			g_env = ms_builtin_setenv(g_env);
	}
	else if (ft_strcmp(g_cmd[0], "unsetenv") == 0)
	{
		if (g_moddedenv == 1)
			env = ms_builtin_unsetenv(env);
		else
			g_env = ms_builtin_unsetenv(g_env);
	}
	else if (ft_strcmp(g_cmd[0], "exit") == 0)
		exit(0);
	return (env);
}

char		*ms_search_bin(char **env)
{
	char	**path;
	char	*pathbin;

	pathbin = NULL;
	path = NULL;
	if (g_cmd[0][0] == '/')
		return (g_cmd[0]);
	if (!env || !env[0])
		path = ft_strsplit(__DEFAULT_PATH__, ':');
	pathbin = ms_search_pathbin(path, env);
	if (!pathbin)
	{
		ft_printf("21sh: command not found: %s\n", g_cmd[0]);
		g_cmd = ms_free_tab(g_cmd);
	}
	return (pathbin);
}

char		*ms_search_pathbin(char **path, char **env)
{
	char	*tmp;
	char	*pathbin;
	int		i;

	i = 0;
	pathbin = NULL;
	if (!path)
		path = ms_get_path(env);
	while (path[i])
	{
		tmp = path[i];
		pathbin = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = pathbin;
		pathbin = ft_strjoin(tmp, g_cmd[0]);
		free(tmp);
		if (access(pathbin, X_OK) > -1)
			return (pathbin);
		i++;
		free(pathbin);
	}
	return (NULL);
}

void		ms_exec_bin(char *pathbin, char **env)
{
	pid_t	pid;
	
	if (!pathbin)
		return ;
	pid = fork();
	if (pid == 0)
		execve(pathbin, g_cmd, env);
	else
		wait(&pid);
	g_cmd = ms_free_tab(g_cmd);
	if (g_moddedenv > 0)
	{
		if (g_i == 0)
			env = ms_free_tab(env);
		g_i = 0;
		g_moddedenv = 0;
	}
}
