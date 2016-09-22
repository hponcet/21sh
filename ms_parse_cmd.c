/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:26:12 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/22 17:12:26 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

static int		ms_get_number(char *buf)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (buf[i])
	{
		while ((buf[i] == ' ' || buf[i] == '	') && buf[i])
		{
			if (buf[i + 1] && buf[i + 1] != ' ' && buf[i + 1] != '	')
				count++;
			i++;
		}
		while (buf[i] != ' ' && buf[i] != '	' && buf[i])
		{
			if (buf[i] && (buf[i] == 39 || buf[i] == '"' || buf[i] == 92))
				i += ft_cmd_count_quote(buf, i, buf[i]);
			if (count == 0)
				count++;
			i++;
		}
	}
	return (count);
}

static char		*ft_strsub_quote(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*buf;
	size_t		j;
	char		c;

	j = 0;
	buf = ft_strnew(len);
	i = (size_t)start + len;
	if (s == NULL || buf == NULL)
		return (NULL);
	while (start < i)
	{
		if (s[start] && (s[start] == 39 || s[start] == '"') && ++start)
		{
			c = s[start - 1];
			while (start < i && s[start] != c)
				buf[j++] = s[start++];
			start++;
		}
		buf[j] = s[start];
		start++;
		j++;
	}
	return (buf);
}

char			**ms_parse_cmd(char *buf)
{
	char	**cmd;
	int		t[4];

	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	t[3] = ms_get_number(buf);
	if (!(cmd = (char**)malloc(sizeof(char*) * (t[3] + 1))))
		return (NULL);
	cmd[t[3]] = NULL;
	while (buf[t[0]] && t[1] < t[3])
	{
		while (buf[t[0]] == ' ' || buf[t[0]] == '	')
			t[0]++;
		t[2] = t[0];
		while (buf[t[0]] != ' ' && buf[t[0]] != '	' && buf[t[0]] != '\0')
		{
			if (buf[t[0]] && (buf[t[0]] == 39 || buf[t[0]] == '"'
						|| buf[t[0]] == 92))
				t[0] += ft_cmd_count_quote(buf, t[0], buf[t[0]]);
			t[0]++;
		}
		cmd[t[1]++] = ft_strsub_quote(buf, t[2], (t[0] - t[2]));
	}
	return (cmd);
}
