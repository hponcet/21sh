/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 12:38:07 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/23 18:07:07 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

void	ms_builtin_env(char **env)
{
	ms_del_cmd(0);
	if (!g_cmd)
	{
		ms_print_env(env);
		return ;
	}
	while (g_cmd && (g_cmd[0][0] == '-' || ft_cindex(g_cmd[0], '=') > -1 ||
				g_cmd[0][0] == 'i' || g_cmd[0][0] == 'u'))
	{
		if (g_cmd[0][0] == '-' || g_cmd[0][0] == 'i' || g_cmd[0][0] == 'u')
		{
			if (g_cmd[0][0] == '-')
				g_cmd[0] = ft_strcut(g_cmd[0], 1);
			env = ms_builtin_env_opt(env);
		}
		if (g_cmd && ft_cindex(g_cmd[0], '=') > -1)
			env = ms_builtin_setenv(env);
	}
	if (g_cmd)
		ms_exec(env);
	else
		ms_print_env(env);
}

char	**ms_builtin_env_opt(char **env)
{
	if (g_cmd[0][0] == 'i')
	{
		if (g_cmd[0][1] != '\0')
			g_cmd[0] = ft_strcut(g_cmd[0], 1);
		else
		{
			if (!g_cmd[1])
				g_cmd = ms_free_tab(g_cmd);
			else
				ms_del_cmd(0);
		}
		env = ms_free_tab(env);
		g_i = 1;
	}
	else if (g_cmd[0][0] == 'u')
		env = ms_builtin_env_opt_u(env);
	else
	{
		ft_printf("21sh: env: illegal option -- %c\n", g_cmd[0][0]);
		ft_printf(" usage: env [-i] [-u name] [name=value ...]\n");
		g_cmd = ms_free_tab(g_cmd);
		env = ms_free_tab(env);
	}
	return (env);
}

char	**ms_builtin_env_opt_u(char **env)
{
	if (g_cmd[0][1] != '\0')
	{
		g_cmd[0] = ft_strcut(g_cmd[0], 1);
		env = ms_builtin_unsetenv(env);
	}
	else
	{
		if (!g_cmd[1])
		{
			ft_printf("21sh: env: illegal option -- u\n");
			ft_printf(" usage: env [-i] [-u name] [name=value ...]\n");
			env = ms_free_tab(env);
			g_cmd = ms_free_tab(g_cmd);
			return (env);
		}
		ms_del_cmd(0);
		env = ms_builtin_unsetenv(env);
	}
	return (env);
}
