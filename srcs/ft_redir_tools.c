/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 17:38:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 21:03:10 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_redir_isgoodchar(char i)
{
	if ((i >= 33 && i <= 126) && i != '|' && i != '<' && i != '>' && i != '\0'
			&& i != '`' && i != ' ' && i != '	')
		return (1);
	else
		return (0);
}

static void	ft_redir_checkifdir(char **filename, char **cmd)
{
	struct stat		s_stat;
	char			*path;
	char			*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAXPATHLEN);
	path = ft_joinf("%xs/%s", pwd, filename[0]);
	lstat(path, &s_stat);
	if (S_ISDIR(s_stat.st_mode)
			|| S_ISCHR(s_stat.st_mode)
			|| S_ISFIFO(s_stat.st_mode)
			|| S_ISLNK(s_stat.st_mode)
			|| S_ISSOCK(s_stat.st_mode)
			|| S_ISWHT(s_stat.st_mode)
			|| S_ISBLK(s_stat.st_mode))
	{
		ft_printf("21sh: %s isn't a file.\n", filename[0]);
		ft_strdel(&path);
		ft_strdel(filename);
		ft_strdel(cmd);
		exit(EXIT_FAILURE);
	}
	ft_strdel(&path);
}

char		*ft_redir_getfilename(char *cmd, char c)
{
	char	*filename;
	int		i;
	int		j;

	i = ft_cindex_noquote_rev(cmd, c) + 1;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '	'))
		i++;
	j = i;
	while (ft_redir_isgoodchar(cmd[j]) == 1)
		j++;
	if (j - i < 1)
	{
		ft_putendl("21sh: Parse error.");
		exit(EXIT_FAILURE);
	}
	filename = ft_strnew(j - i);
	j = 0;
	while (cmd[i] && ft_redir_isgoodchar(cmd[i]) == 1)
	{
		filename[j] = cmd[i];
		j++;
		i++;
	}
	ft_redir_checkifdir(&filename, &cmd);
	return (filename);
}
