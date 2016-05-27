/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 01:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/05/27 16:22:44 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_ast(char *cmd)
{
	char	**pipetab;
	int		i;
	pid_t pid;

	i = 0;
	pipetab = ft_strsplit(cmd, '|');
	while (pipetab[i + 1])
		i++;
	pid = fork();
	if (pid == 0)
	{
		while (i > 0)
		{
			ft_printf("\n\ni == %d\n\n", i);
			ft_pipe(pipetab[i - 1], pipetab[i]);
			ft_printf("\nexit ft_pipe\n");
			i -= 2;
		}
		if (i == 0)
		{
			g_cmd = ms_get_cmd(pipetab[i]);
			ms_exec(g_env);
		}
	}
	else
		wait(&pid);
}

void		ft_pipe(char *cmd1, char *cmd2)
{
	int pipefd[2];
	pid_t pid;

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
			ft_printf("\ncmd2\n");
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		g_cmd = ms_get_cmd(cmd2);
		ms_exec(g_env);
	}
	else
	{
			ft_printf("\ncmd1\n");
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		g_cmd = ms_get_cmd(cmd1);
		ms_exec(g_env);
	}
			ft_printf("\nexit\n");
	exit(0);
			ft_printf("\nexit\n");
}
