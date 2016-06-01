/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 22:44:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/01 15:15:01 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int		ft_redir_do(char *cmd)
{
	int		i;
	char	*word;
	int		*tab_quote;
	char	*ret;

	if ((i = ft_cindex(cmd, '<')) > 0 && cmd[i + 1] == '<')
	{
		while (cmd[i] == ' ' || cmd[i] == '	')
			i++;
		word = ft_strsub(cmd, i, ft_strlen(cmd) - i);

		ret = NULL;
		if (g_tmpchain)
		{
			if (!g_retval)
				ret = ft_strdup(g_tmpchain);
			else
				ret = ft_strjoin(g_tmpchain, g_retval);
			free(g_tmpchain);
			g_tmpchain = NULL;
		}
		else
			ret = ft_strdup(g_retval);
		tab_quote = ft_quote_find(ret);
		if (ft_quote_prompt(tab_quote) > 0)
		{
			g_tmpchain = ret;
			return (1);
		}
		g_curs.qt = 0;
		g_retval = NULL;
		g_retval = ft_strdup(ret);
		free(ret);
	}
	return (0);
}
