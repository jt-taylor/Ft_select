/ */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 09:27:17 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/17 20:53:03 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compiler needs to link to the library , '-ltermcap or -ltermlib'
#ifndef FT_SELECT_H
# define FT_SELECT_H

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
**  our stucture , not sure wether to make it a global or to just pass it 
**  between evey function
*/

typedef struct	s_select
{
	char		*term_name;
}				t_select

extern t_select			g_select;

/*
** ft_select_signal.c
*/

void	ft_select_signal_handler(int signo);

/*
** ft_select_init_termcaps.c
*/
void		init_termcap(char **env);

/*
** ft_select_main.c
*/
void		ft_exit_err(char *str, int exit_code);

#endif
