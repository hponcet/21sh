/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:05:16 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/21 15:47:03 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		*ft_quote_initteub(void)
{
	int		*teub;

	teub = (int*)malloc(sizeof(int) * 5);
	teub[0] = 0;
	teub[1] = 0;
	teub[2] = 0;
	teub[3] = 0;
	teub[4] = 0;
	return (teub);
}

static int		*ft_quote_find(char *retval)
{
	int			*tab_quote;
	int			i;

	tab_quote = ft_quote_initteub();
	i = 0;
	while (retval[i])
	{
		if (retval[i] == 39)  // '
			tab_quote[0] = (tab_quote[0] == 0) ? 1 : 0;
		if (retval[i] == 34)  // "
			tab_quote[1] = (tab_quote[1] == 0) ? 1 : 0;
		if (retval[i] == 96)  // `
			tab_quote[2] = (tab_quote[2] == 0) ? 1 : 0;
		if (retval[i] == '{') // {
			tab_quote[3]++;
		if (retval[i] == '}') // }
			tab_quote[3]--;
		if (retval[i] == '(')  // (
			tab_quote[4]++;
		if (retval[i] == ')')  // )
			tab_quote[4]--;
		i++;
	}
	return (tab_quote);
}

static int			ft_quote_prompt(int *tab_quote)
{
	if (tab_quote[0] > 0 || tab_quote[1] > 0 || tab_quote[2] > 0 ||
			tab_quote[3] > 0 || tab_quote[4] > 0)
	{
		if (tab_quote[0] > 0)
			ft_putstr_fd("quote ", g_fd);
		if (tab_quote[1] > 0)
			ft_putstr_fd("dquote ", g_fd);
		if (tab_quote[2] > 0)
			ft_putstr_fd("bquote ", g_fd);
		if (tab_quote[3] > 0)
			ft_putstr_fd("cursh ", g_fd);
		if (tab_quote[4] > 0)
			ft_putstr_fd("subsh ", g_fd);
		ft_putstr_fd("> ", g_fd);
		return (1);
	}
	return (0);
}

int				ft_quote(void)
{
	int		*tab_quote;
	char	*ret;

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
	return (0);
}
