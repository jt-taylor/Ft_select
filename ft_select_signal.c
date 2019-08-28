/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 10:33:05 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 12:41:51 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_select_reset_default_term_config(void)
{
	tcsetattr(2, TCSANOW, &g_select.old_attr);
	tputs(tgetstr("ve", NULL), 1, ft_select_putchar);
	tputs(tgetstr("te", NULL), 1, ft_select_putchar);
}

/*
** signal handle for sig susspend
*/

static void	handle_signal_suspend(void)
{
	ft_select_reset_default_term_config();
	signal(SIGTSTP, SIG_DFL);
	ioctl(2, TIOCSTI, "\x1A");
}

/*
** signal handle for sigkill etc ...
*/

void		handle_signal_exit(void)
{
	ft_select_reset_default_term_config();
	exit(0);
}

/*
** handle signal initialization
** SIGKILL AND SIGSTOP are only allowed to be handled by the kernal
*/

void		ft_select_signal_handler(int signo)
{
	if (signo == SIGTSTP)
		handle_signal_suspend();
	else if (signo == SIGCONT)
	{
		set_custom_config();
		ft_select_signal_handle();
		ioctl(2, TIOCSTI, "1");
	}
	else if (signo == SIGWINCH)
		ft_select_display_args();
	else if (signo == SIGINT || signo == SIGABRT || signo == SIGQUIT)
		handle_signal_exit();
}
