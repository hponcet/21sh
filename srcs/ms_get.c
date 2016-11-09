/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 13:48:10 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/08 12:42:10 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

char		*ms_get_value(char **env, char *name)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = ft_strlen(name);
	ret = NULL;
	while (env && env[j])
	{
		if (ft_strncmp(name, env[j], i) == 0 && env[j][i] == '=')
		{
			ret = ft_strdup(env[j] + i + 1);
			return (ret);
		}
		j++;
	}
	return (NULL);
}

char		**ms_get_path(char **env)
{
	int		j;
	char	**ret;

	j = 0;
	ret = NULL;
	if (env && env[j])
	{
		while (!(ft_strncmp("PATH", env[j], 4) == 0 && env[j][4] == '='))
			j++;
		if (env[j] && ft_strncmp("PATH", env[j], 4) == 0 && env[j][4] == '=')
			ret = ft_strsplit(env[j] + 5, ':');
	}
	return (ret);
}

char		**ms_get_env(char **env)
{
	char	**renv;
	int		i;

	renv = NULL;
	i = 0;
	if (!env)
		return (renv);
	while (env[i])
		i++;
	if (!(renv = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	renv[i] = NULL;
	i = 0;
	while (env[i])
	{
		renv[i] = ft_strdup(env[i]);
		i++;
	}
	return (renv);
}

void		ms_print_env(char **env)
{
	int		i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

int			ms_get_point(char **cmd)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	if (ft_strncmp(cmd[0], "./", 2))
	{
		tmp = getcwd(tmp, MAXPATHLEN);
		tmp2 = ft_strsub(cmd[0], 2, ft_strlen(cmd[0]) + ft_strlen(tmp) - 1);
		tmp3 = ft_strjoin(tmp, tmp2);
		cmd[0] = ft_strdup(tmp3);
		ft_tabdel(g_cmd);
		g_cmd = ms_parse_cmd(cmd[0]);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		ft_strdel(&tmp3);
	}
	return (1);
}
