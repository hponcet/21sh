/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:15:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/07 19:32:47 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_isemptystring(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

char		**ft_cmd_delemptycmd(char **cmd)
{
	char	**ret;
	int		i;
	int		j;

	ret = NULL;
	if (!cmd)
		return (NULL);
	i = 0;
	j = -1;
	while (cmd[++j])
	{
		if (ft_isemptystring(cmd[j]) == 0)
			i++;
	}
	if (i == 0)
		return (NULL);
	ret = (char**)malloc(sizeof(char*) * i + 1);
	ret[i] = NULL;
	j = -1;
	i = -1;
	while (cmd[++j])
	{
		if (ft_isemptystring(cmd[j]) == 0)
			ret[++i] = ft_strdup(cmd[j]);
	}
	ms_print_env(ret);
	return (ret);
}
