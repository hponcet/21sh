/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:25:03 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 02:29:48 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_glob_count_quote_rev(char *s, int i, char c)
{
	int		j;

	j = 1;
	i--;
	while (s[i] != c && s[i])
	{
		i--;
		j++;
	}
	return (j);
}

int			ft_glob_check(char *str)
{
	int		len;

	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if (str[len] == '[' || str[len] == '?' || str[len] == '*'
			|| str[len] == '{')
			return (1);
		if (str[len] == '\"' || str[len] == '\'' || str[len] == 96)
			len -= ft_glob_count_quote_rev(str, len, str[len]);
		len--;
	}
	return (0);
}

char		**ft_glob(char **cmd)
{
	int		i;
	char	*ncmd;
	char	**ret;

	i = 0;
	ncmd = NULL;
	while (cmd[i])
	{
		if (ft_glob_check(cmd[i]))
			cmd[i] = ft_glob_replace(cmd[i]);
		ncmd = ft_joinf("%s %s", ncmd, cmd[i]);
		i++;
	}
	ret = ft_strsplit(ncmd, ' ');
	ft_tabdel(cmd);
	return (ret);
}

int			ft_glob_compare(char *s1, char *s2)
{
	//ft_printf("%s\n", s1);
	//ft_printf("%s\n", s2);
	if ((!*s1 && !*s2))								// fin de chaine
		return (1);
	else if (*s1 == '?' && *s2)						// ? : avance d'un char
		return (ft_glob_compare(s1 + 1, s2 + 1));
	else if (*s1 == '*' && s1[1] == '*')			// * : multiple *
		return (ft_glob_compare(s1 + 1, s2));
	else if (*s1 == '*' && *s2 == s1[1])			// * : match
		return (ft_glob_compare(s1 + 1, s2) || ft_glob_compare(s1, s2 + 1));
	else if (*s1 == '*' && *s2 != s1[1] && *s2)		// * : avance sur s2
		return (ft_glob_compare(s1, s2 + 1));
	else if (*s1 == '\\' && (s1[1] == '*'			// \ : echapement
				|| s1[1] == '?' || s1[1] == '{'
				|| s1[1] == '[') && *s2 == s1[1])
		return (ft_glob_compare(s1 + 2, s2 + 1));
	else if (*s1 == *s2)							// char identique
		return (ft_glob_compare(s1 + 1, s2 + 1));
	return (0);
}
