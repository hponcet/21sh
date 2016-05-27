/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 01:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/27 10:37:43 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_ast(char *cmd)
{
	char	**atab;
	int		i;

	i = 0;
	atab = ft_strsplit(cmd, '|');
	while (atab[i])
		i++;
	i--;
	while (i >= 0)
	{
		ft_pipe(atab[i - 1], atab[i]);
		i -= 2;
	}
}

void		ft_pipe(char *cmd1, char *cmd2)
{
	int pipefd[2];
	pid_t pid;

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		g_cmd = ms_get_cmd(cmd2);
		ms_exec(g_env);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		g_cmd = ms_get_cmd(cmd1);
		ms_exec(g_env);
	}
}
