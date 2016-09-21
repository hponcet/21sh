/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_config.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 12:48:34 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/21 10:10:47 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_CONFIG_H
# define MS_CONFIG_H
# include "../libft/includes/ft_colors.h"



/*
** ***************************
** Buffer length of read loop
** ***************************
** This buffer catch all keys entered on the
** keyboard and the the pasteboard if the Cmd-V
** is entered.
*/
# define __BUFLEN__ 2048

/*
** ***************************
** Default path if env is NULL
** ***************************
** In this case, separate paths with ':' if some
** paths are required.
*/
# define __DEFAULT_PATH__ "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

/*
** ***************************
** Default path if env is NULL
** ***************************
** In this case, separate paths with ':' if some
** paths are required.
*/
# define __DEFAULT_HOME__ ""

/*
** ********************
** Name of prompt shell
** ********************
** You can find all the declensions of colors and
** text formatting in the file "../libft/includes
** /ft_colors.h"
*/

# define __PROMPT_NAME__ __CYA"✱  "
/*
** ********************************
** Curent directory of prompt shell
** ********************************
** You can find all the declensions of colors and
** text formatting in the file "../libft/includes
** /ft_colors.h".
** For (de)activate directory, set __PROMPT_DIR__
** to [Y/N].
*/
# define __PROMPT_DIR__ "Y"
# define __DIR_COLOR__ __BLD __WHT
# define __DIR_COLOR_END__ " "__CLR_END__

/*
** *********************************
** Activate graphic Debug Mode [Y/N]
** *********************************
*/
# define __DEBUG__ "N"

#endif
