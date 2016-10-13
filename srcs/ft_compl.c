/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:36:51 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/13 23:31:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_compl		*ft_compl_makechain(char *path)
{
	DIR				*dirp;
	struct dirent	*s_dir;
	t_compl			*file;
	t_compl			*ret;

	ret = NULL;
	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((s_dir = readdir(dirp)) != NULL)
	{
		file = (t_compl*)malloc(sizeof(t_compl));
		if (!file)
			return (NULL);
		file->name = ft_strdup(s_dir->d_name);
		if (DT_DIR(s_dir->d_type))
			file->type = 1;
		else
			file->type = 0;
		file->next = NULL;
		ft_compl_sortchain(&ret, file);
	}
	closedir(dirp);
	return (ret);
}

void		ft_compl_sortchain(t_compl **list, t_compl *file)
{
	t_compl	*tmp;

	tmp = *list;
	if (!tmp)
	{
		*list = file;
		return ;
	}
	if (ft_strcmp(tmp->name, file->name) > 0)
	{
		file->next = tmp;
		*list = file;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->next, file) < 0)
		tmp = tmp->next;
	file->next = tmp->next;
	tmp->next = file;
}

int			ft_compl_wis(char *str)
{
	int		i;
	int		j;

	i = ft_strlen(str) - 1;
	j = 0;
	while (str[j] && (str[j] == ' ' || str[j] == '	'))
		j++;
	while (i >= j)
	{
		if (str[i] == ' ' && i > 0 && str[i - 1] != ' ' && str[i - 1] != ';'
				&& str[i - 1] != '`')
			return (1);
		if (str[i] == ';' || str[i] == '`')
			return (0);
		i--;
	}
	return (0);
}

void		ft_compl_file(char *str)
{
	char	*path;
	char	*pwd;
	int		i;

	i = ft_cindex_rev(str, '/');
	pwd = getcwd(pwd, MAXPATHLEN);
	path = ft_joinf
}

char		*ft_compl(char *str)
{
	if (ft_compl_wis(str) == 1)
		ft_compl_file(str);
	else
		ft_compl_bin(str);
}
