/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 21:27:35 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/07 02:14:29 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static unsigned int	ft_count_word(char const *s)
{
	size_t				i;
	unsigned int		count;

	count = 0;
	i = 0;
	if (s[0] != ';' && s[0] != '\0')
		count++;
	while (s[i])
	{
		if (s[i] == 92)
			i++;
		if (s[i] == 39)
			while (s[++i] != 39)
				;
		if (s[i] == '"')
			while (s[++i] != '"')
				;
		if ((s[i] == ';' && s[i + 1] != ';' && s[i + 1] != '\0') || (s[i] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char			**ft_cmd_parse(char **teub, char const *s)
{
	int		i;
	int		j;
	size_t	start;

	start = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 92)
			i++;
		if (s[i] && s[i] == 39 && ++i)
			while (s[i] != 39 && s[i])
				i++;
		if (s[i] && s[i] == '"' && ++i)
			while (s[i] != '"' && s[i])
				i++;
		if (s[i] == ';' || !s[i])
		{
			teub[j] = ft_strsub(s, start, (i - start));
			j++;
			if (!s[i])
				return (teub);
			while (s[i] && s[i] == ';')
				i++;
			start = i + 1;
		}
		if (!s[i])
			return (teub);
		i++;
	}
	return (teub);
}

char				**ft_cmd_split(char const *s)
{
	size_t	len;
	char	**teub;

	if (!s)
		return (NULL);
	len = ft_count_word(s);
	teub = (char**)malloc(sizeof(char*) * (len + 1));
	teub[len] = NULL;
	teub = ft_cmd_parse(teub, s);
	return (teub);
}
