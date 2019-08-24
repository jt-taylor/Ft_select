/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 10:33:05 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/23 21:31:04 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_select_reset_default_term_config(void)
{
	tcsetattr(2, TCSANOW, &g_select.old_attr);
	tputs(tgetstr("ve", NULL), 1, ft_select_putchar);
	tputs(tgetstr("te", NULL), 1, ft_select_putchar);
}

/*
** signal handle for sig susspend
*/

static void		handle_signal_suspend(void)
{
	//reset terminal conf
	//set default action for SIGTSTP && SIGSTOP
}

/*
** signal handle for sigkill etc ...
*/

void		handle_signal_exit(void)
{
	//reset termial
	ft_select_reset_default_term_config();
	//free anything
	printf("Got to hanlde_signal_stop\n");
	exit(0);
}

/*
** handle signal initialization
** SIGKILL AND SIGSTOP are only allowed to be handled by the kernal
*/

void	ft_select_signal_handler(int signo)
{
	if (signo == SIGTSTP)
		//this is the ctrl + z
		// 'pauses' the program 
		// SIGTSTP and SIGSTOP are slightly different
		// SIGSTOP is sent from someting like kill -STOP pid
		// while SIGTSTP can be sent via tty (ie keyboard);
		//  !!!    SIGSTOP can't be ignored but SIGTSTP might be
		handle_signal_suspend();
	else if (signo == SIGCONT)
		//handle process resume
		// handle preocess already runnnig resume
		;
	else if (signo == SIGWINCH)
		//handle window resize;
		;
	else if (signo == SIGINT || signo == SIGABRT || signo == SIGQUIT)
		// handle sig	-interupt
		//				-abort
		//				-kill
		//				-quit
		handle_signal_exit();
}
