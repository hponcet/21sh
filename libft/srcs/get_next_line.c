/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 17:59:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/18 04:49:49 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int const fd, char **line)
{
	char		*buf;
	int			eof;
	static char	*afternext;

	buf = ft_strnew(BUFF_SIZE + 1);
	line[0] = ft_strnew(0);
	if (ft_afternext(&afternext, line) > 0)
		return (1);
	while ((read(fd, buf, BUFF_SIZE)) > 0)
	{
		if ((eof = ft_cindex(buf, '\n')) >= 0)
		{
			ft_tormoilzboub(buf, eof, line, &(afternext));
			return (1);
		}
		line[0] = ft_strjoin(line[0], buf);
		ft_bzero(buf, BUFF_SIZE);
	}
	if (line[0][0])
		return (1);
	if ((read(fd, buf, BUFF_SIZE)) < 0 || line == NULL)
		return (-1);
	return (0);
}

int		ft_afternext(char **afternext, char **line)
{
	int		i;
	char	*tmp;

	if (*afternext != NULL)
	{
		i = ft_cindex(*afternext, '\n');
		if (i >= 0)
		{
			line[0] = ft_strsub(*afternext, 0, i);
			tmp = ft_strdup(*afternext + i + 1);
			free(*afternext);
			*afternext = tmp;
			return (1);
		}
		else
		{
			line[0] = ft_strjoin(line[0], *afternext);
			ft_bzero(*afternext, ft_strlen(*afternext));
			*afternext = NULL;
			return (0);
		}
	}
	return (0);
}

void	ft_tormoilzboub(char *buf, int eof, char **line, char **afternext)
{
	char	*beforenext;

	beforenext = ft_strsub(buf, 0, eof);
	line[0] = ft_strjoin(line[0], beforenext);
	free(beforenext);
	afternext[0] = ft_strdup(buf + eof + 1);
	free(buf);
	return ;
}
