/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:47:22 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/22 15:35:40 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compiler needs to link to the library , '-ltermcap or -ltermlib'
#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "ft_printf.h"

/*
** ERROR macros
*/

#define GEN_TERM_ERR 0x1


/*
** structre for the args
*/

typedef struct		s_arg
{
	char	*arg_name;
	int		selected;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

// not sure if I want 2 structures with one being the active and one being
// all of them
// or just one for all the args but also store an int for wether it is selected

/*
**  our stucture , not sure wether to make it a global or to just pass it 
**  between evey function
*/

typedef struct	s_select
{
	char		*term_name;
	char		termbuffer[2048];
	struct termios	old_attr;
	struct termios	attr;
	t_arg		*arg_list;
	int			total_count;
	int			total_selected;
}				t_select;

t_select		g_select;
/*
** ft_select_assorted_funcions.c
*/
int		ft_select_putchar(int c);

/*
** ft_select_init_argument_list.c
*/
void		ft_select_init_args(char **arg);

/*
** ft_select_init_termcaps.c
*/
void		init_termcap(char **env);

/*
** ft_select_signal.c
*/
void	ft_select_signal_handler(int signo);

/*
** ft_select_handle_key_press.c
*/
void		ft_select_handle_key_press(void);

/*
** ft_select_main.c
*/
void		ft_exit_err(char *str, int exit_code);

#endif
