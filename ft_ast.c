/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 01:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/02 20:27:40 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_ast(char *cmd)
{
	char	*cmd1;
	char	*cmd2;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (cmd[len])
	{
		if (cmd[len] == '|')
			j = len;
		len++;
	}
	cmd1 = ft_strsub(cmd, 0, j);
	cmd2 = ft_strsub(cmd, j + 1, (ft_strlen(cmd) - j));
	free(cmd);
	ft_pipe(cmd1, cmd2);
	free(cmd1);
	free(cmd2);
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
		ms_exec(cmd2, g_curs.env);
		wait(&pid);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ms_exec(cmd1, g_curs.env);
	}
	exit(0);
}
