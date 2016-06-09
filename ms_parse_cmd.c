/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:26:12 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/09 15:00:35 by hponcet          ###   ########.fr       */
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
			{
				buf[j] = s[start];
				start++;
				j++;
			}
			start++;
		}
		buf[j] = s[start];
		start++;
		j++;
	}
	return (buf);
}

char	**ms_parse_cmd(char *buf)
{
	char	**cmd;
	int		i;
	int		j;
	int		start;
	int		len;

	i = 0;
	j = 0;
	start = 0;
	len = ms_get_number(buf);
	if (!(cmd = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	cmd[len] = NULL;
	while (buf[i] && j < len)
	{
		while (buf[i] == ' ' || buf[i] == '	')
			i++;
		start = i;
		while (buf[i] != ' ' && buf[i] != '	' && buf[i] != '\0')
		{
			if (buf[i] && (buf[i] == 39 || buf[i] == '"' || buf[i] == 92))
				i += ft_cmd_count_quote(buf, i, buf[i]);
			i++;
		}
		cmd[j] = ft_strsub_quote(buf, start, (i - start));
		j++;
	}
	return (cmd);
}
