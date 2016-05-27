/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:46:29 by hponcet           #+#    #+#             */
/*   Updated: 2016/01/18 16:45:02 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buf;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buf = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (buf == NULL)
		return (NULL);
	while (s1[++i] != '\0' && s1 != NULL)
		buf[++j] = s1[i];
	i = -1;
	while (s2[++i] != '\0' && s2 != NULL)
		buf[++j] = s2[i];
	return (buf);
}
