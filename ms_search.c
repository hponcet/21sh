/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:45:06 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/15 17:16:18 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

char		**ms_search_builtin_env(char *cmd, char **env)
{
	if (ft_strcmp(g_cmd[0], "env") == 0)
	{
		if (g_moddedenv == 0)
			env = ms_get_env(g_env);
		g_moddedenv += 1;
		ms_builtin_env(cmd, env);
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
	{
		ft_term_reset();
		exit(0);
	}
	return (env);
}

char		*ms_search_bin(char **env)
{
	char	**path;
	char	*joinpath;
	char	*pathbin;

	pathbin = NULL;
	path = NULL;
	if (g_cmd && g_cmd[0] && g_cmd[0][0] == '/')
		return (g_cmd[0]);
	if ((joinpath = ms_get_value(env, "PATH")))
		path = ft_strsplit(joinpath, ':');
	else
		path = ft_strsplit(__DEFAULT_PATH__, ':');
	pathbin = ms_search_pathbin(path, env);
	if (!pathbin)
	{
		ft_putstr_fd("21sh: command not found: ", g_fd);
		ft_putendl_fd(g_cmd[0], g_fd);
		g_cmd = ms_free_tab(g_cmd);
	}
	ft_strdel(&joinpath);
	free(path);
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
	while (path && path[i])
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
