/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_getinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:01:19 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/14 15:24:16 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_compl		*ft_compl_makechain(char *path, t_compl *ret)
{
	DIR				*dirp;
	struct dirent	*s_dir;
	t_compl			*file;

	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((s_dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(s_dir->d_name, "..") == 0 || ft_strcmp(s_dir->d_name, ".") == 0)
			continue ;
		file = (t_compl*)malloc(sizeof(t_compl));
		if (!file)
			return (NULL);
		file->name = ft_strdup(s_dir->d_name);
		file->type = 0;
		file->x = 0;
		file->y = 0;
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
	while (tmp->next && ft_strcmp(tmp->name, file->name) < 0)
		tmp = tmp->next;
	file->next = tmp->next;
	tmp->next = file;
}

char		*ft_compl_getpath(char *str)
{
	int		i;
	int		j;
	char	*path;
	char	*tmp;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAXPATHLEN);
	path = NULL;
	i = ft_strlen(str) - 1;
	j = 0;
	if (str[i] == ' ')
		return (pwd);
	while (i >= 0 && str[i] != ' ' && str[i] != ';' && str[i] != '/')
		i--;
	if (i == 0 || str[i] == ' ' || str[i] == ';')
		return (pwd);
	if (str[i] == '/')
	{
		j = ft_cindex_rev(str, ' ');
		tmp = ft_strsub(str, j, i - j + 1);
		path = ft_joinf("%xs/%xs/", pwd, tmp);
	}
	return (path);
}

char		*ft_compl_getfind(char *str)
{
	int		i;
	int		j;
	char	*find;

	find = NULL;
	i = ft_strlen(str) - 1;
	j = i;
	if (str[i] == ' ')
		return (NULL);
	while (i >= 0 && str[i] != ' ' && str[i] != '/')
		i--;
	i++;
	if (str[i - 1] == '/' || str[i - 1] == ' ')
		find = ft_strsub(str, i, j - i + 1);
	return (find);
}
