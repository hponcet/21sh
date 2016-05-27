/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gus <Gus@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:36:33 by Gus               #+#    #+#             */
/*   Updated: 2016/05/25 17:56:54 by Gus              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_pipe(char *cmd)
{
	int		pfd[2];
	int		pid;

	pipe(pfd);
	if ((pid = fork()) < 0)
		return 2;
	if (pid == 0)
	{
		close(pfd[1]);
		/* lire dans pfd[0] */
		close(pfd[0]);
	}
	else
	{
		close(pfd[0]);
		/* ecrire dans pfd[1] */
		close(pfd[1]);
	}
	return (0);
}
