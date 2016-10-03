/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 20:03:31 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/03 17:58:19 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_colors.h"
# include "ms_minishell.h"
# include "ft_config.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/param.h>

typedef struct		s_hd
{
	char			*init_cmd;
	char			*cmd;
	char			*trigger;
}					t_hd;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_term
{
	struct termios	mod;
	struct termios	init;
	struct termios	curs_pos;
}					t_term;

typedef struct		s_chain
{
	char			c;
	size_t			word;
	size_t			sel;
	int				*cp;
	size_t			id;
	struct s_chain	*next;
	struct s_chain	*prev;
}					t_chain;

typedef struct		s_curs
{
	int				*curs_pos;
	int				*ws;
	int				hist;
	int				qt;
	size_t			nb_chr;
	size_t			id;
	struct s_chain	*select;
	struct s_chain	*ls;	// LAST CHAR
	struct s_chain	*next;
	struct s_chain	*prev;
	t_hd			*hd;
	int				fd;
	char			**env;
	int				*initpos;
	t_term			term;
	t_chain			*chain;
	char			*tmpchain;
	char			*copy;
	t_hist			*history;
	char			*retval;
	int				error;
}					t_curs;

t_curs				g_curs;

/*
** ft_dollar.c
*/
char				*ft_get_env_value(char *cmd);
char				*ft_get_var_value(char *str);
char				*ft_replace_cmd_var(char *cmd, char *var, char *value);
char				*ft_dollar(char *str);

/*
** ft_redir_heredoc.c
*/
int					ft_heredoc_check(void);
int					ft_heredoc_new(void);
void				ft_heredoc_del(void);
void				ft_heredoc_proc(void);
int					ft_heredoc_exec(char *str);
int					ft_heredoc_addcontent(char *str);
int					ft_heredoc_endtrig(char *str);
char				*ft_heredoc_initcmd(char *str);
char				*ft_heredoc_cmd(char *str);
void				ft_heredoc_err(int i);

/*
** ft_bquote.c
*/
void				ft_cmd_v(char *buf);
/*
** ft_bquote.c
*/
char				*ft_bquote(char *cmd);

/*
** ft_redir_fd.c
*/
void				ft_redir_fd(char *cmd);

/*
** ft_redir_fd_left.c
*/
void				ft_redir_fd_left(char *cmd);

/*
** ft_redir_fd_right.c
*/
void				ft_redir_fd_right(char *cmd);

/*
** ft_redir.c
*/
void				ft_redir(char *cmd);
void				ft_redir_left(char *cmd);

/*
** ft_redir_right.c
*/
void				ft_redir_right(char *cmd);
void				ft_redir_recurs_right(char *cmd);

/*
** ft_redir_right.c
*/
void				ft_redir_double_right(char *cmd);
void				ft_redir_recurs_double_right(char *cmd);

/*
** ft_ast.c
*/
void				ft_ast(char *cmd);
void				ft_pipe(char *cmd1, char *cmd2);

/*
** ft_cursor_pos.c
*/
void				get_fd(void);
void				ft_cursor_pos(void);
int					ft_term_init(void);
int					ft_term_reset(void);

/*
** ft_sh_name.c
*/
char				*ms_shell_name(void);
char				*ms_shell_name_getdir(void);
void				ft_put_name(void);

/*
** ft_signal.c
*/
void				ft_signal(void);
void				ft_signal_onexec(void);
void				ft_init_prompt(void);

/*
** ft_window_size.c
*/
void				ft_window_size(void);

/*
** ft_history.c
*/
void				ft_history(char *cmd);

/*
** ft_display.c
*/
void				ft_display(void);

/*
** ft_init.c
*/
void				ft_load(void);
void				ft_init(void);
void				ft_init_window(void);
/*
** ft_history.c
*/
void				ft_init_hist(void);
void				ft_hist_addtohist(char *ncmd);
void				ft_histtochain(void);

/*
** ft_quote.c
*/
int					ft_quote(void);
int					*ft_quote_initteub(void);

/*
** ft_key.c
*/
void				ft_key(char *buf);
void				ft_key_group_dir(char *buf);

/*
** ft_chain.c
*/
void				ft_chain_addchar(int c);
void				ft_chain_firstchar(int c);
void				ft_chain_midchar(int c);
void				ft_chain_lastchar(int c);
t_chain				*ft_new_chr(int c);

/*
** ft_chain_tools.c
*/
void				ft_init_pos(void);
int					ft_count_chain(void);
void				ft_find_word(void);
void				ft_make_retval(void);
void				ft_del_chain(void);

/*
** ft_char.c
*/
int					ft_char(int i);
int					ft_char_tc(t_chain *chr);
int					ft_str_tc(t_chain *chr);

/*
** ft_key_directional.c
*/
void				ft_key_directional(const char *buf);
void				ft_key_left(void);
void				ft_key_right(void);

/*
** ft_key_up.c
*/
void				ft_key_up(void);

/*
** ft_key_down.c
*/
void				ft_key_down(void);

/*
** ft_key_shift_dir_right.c
*/
void				ft_shift_dir_right(void);
void				ft_reset_select(void);

/*
** ft_key_shift_dir_left.c
*/
void				ft_shift_dir_left(void);
/*
** ft_key_enter.c
*/
void				ft_key_enter(void);

/*
** ft_key_bs.c
*/
void				ft_key_bs(void);

/*
** ft_key_del.c
*/
void				ft_key_del(void);

/*
** ft_key_del.c
*/
void				ft_key_home(char *buf);

/*
** ft_key_opt_directional.c
*/
void				ft_key_opt_directional(char *buf);

/*
** ft_key_opt_copy.c
*/
void				ft_func_copy(char *buf);
void				ft_copy(void);
void				ft_paste(void);
void				ft_cut(void);

/*
** ft_debug.c
*/
void				ft_debug(void);

#endif


/*
   me      Fin de tous les modes tels que so, us, mb, md et mr
   us      Début de soulignement
   md      Début de mode gras
   mr      Début de mode inverse
   sc		save pos curs
   rc		restor pos curs
   cm		cursor move
   up		^
   do		v
   nd		>
   le		<
   cb      Effacer depuis le début de la ligne jusqu'au curseur
   dc      Effacer 1 caractères
   ce	   Effacer jusqu'a la fin de la ligne
   do      Descendre le curseur d'une ligne
   ll	   Déplacer le curseur au coin inférieur gauche
*/
