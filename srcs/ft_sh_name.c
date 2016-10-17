/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:04:19 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/16 22:43:59 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_put_name(void)
{
	char	*prompt;

	prompt = ms_shell_name();
	ft_putstr_fd(prompt, g_curs.fd);
	free(prompt);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
}

char	*ms_shell_name(void)
{
	char	*name;
	char	*dir;
	char	*tmp;

	name = ft_strdup(__PROMPT_NAME__);
	if (__PROMPT_DIR__ == "Y")
	{
		dir = ms_shell_name_getdir();
		tmp = ft_strjoin(__DIR_COLOR__, dir);
		free(dir);
		dir = ft_strjoin(tmp, __DIR_COLOR_END__);
		free(tmp);
	}
	else
		dir = ft_strdup("");
	tmp = ft_strjoin(name, dir);
	if (tmp[0] == '\0')
		tmp = ft_strdup("21sh $> ");
	free(name);
	free(dir);
	return (tmp);
}

char	*ms_shell_name_getdir(void)
{
	char	*tmp;
	char	*dir;
	int		i;
	int		j;

	i = 0;
	tmp = NULL;
	tmp = getcwd(tmp, MAXPATHLEN);
	if (tmp)
	{
		j = ft_strlen(tmp);
		while (tmp[--j] != '/')
			i++;
		if (!(dir = (char*)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		dir[i] = '\0';
		i = -1;
		while (tmp[++j])
			dir[++i] = tmp[j];
	}
	if (i == 0 || i == -1)
		dir = ft_strdup("/");
	free(tmp);
	return (dir);
}
