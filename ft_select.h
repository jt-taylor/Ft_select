/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:47:22 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 13:17:16 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/signal.h>
# include "libft.h"
# include "ft_printf.h"

/*
** ERROR macros
*/

# define GEN_TERM_ERR 0x1

/*
** structre for the args
*/

typedef struct	s_arg
{
	char			*arg_name;
	int				selected;
	struct s_arg	*head;
	struct s_arg	*next;
	struct s_arg	*prev;
}				t_arg;

/*
**  our stucture , not sure wether to make it a global or to just pass it
**  between evey function
*/

typedef struct	s_select
{
	char			*term_name;
	char			termbuffer[2048];
	struct termios	old_attr;
	struct termios	attr;
	t_arg			*arg_list;
	t_arg			*current_cursor;
	int				total_count;
	int				total_selected;
	int				ac;
	char			**environ;
}				t_select;

t_select		g_select;
/*
** ft_select_assorted_funcions.c
*/
int				ft_select_putchar(int c);
int				get_term_size(int return_width_or_height);
int				ft_select_count_columns(void);

/*
** ft_select_init_argument_list.c
*/
void			ft_select_init_args(char **arg);

/*
** ft_select_init_termcaps.c
*/
void			init_termcap(char **env);

/*
** ft_select_signal.c
*/
void			ft_select_signal_handler(int signo);
void			handle_signal_exit(void);
void			ft_select_reset_default_term_config(void);

/*
** ft_select_handle_key_press.c
*/
void			ft_select_display_args(void);
void			ft_select_handle_key_press(void);

/*
** ft_select_handle_space_and_lr_arrows.c
*/
void			ft_select_handle_space(void);
void			ft_select_handle_right_arrow(void);
void			ft_select_handle_left_arrow(void);
void			ft_select_remove_arg();

/*
** ft_select_handle_enter_key
*/
void			ft_select_handle_enter_key(void);

/*
** ft_select_main.c
*/
void			ft_exit_err(char *str, int exit_code);
void			set_custom_config(void);
void			ft_select_signal_handle(void);

#endif
