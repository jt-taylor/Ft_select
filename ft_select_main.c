/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:00:00 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 12:18:54 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Notes :
** termios structure contains at least
** * tcflag_t c_iflag;      / input modes
** * tcflag_t c_oflag;      / output modes
** * tcflag_t c_cflag;      / control modes
** * tcflag_t c_lflag;      / local modes
** * cc_t     c_cc[NCCS];   / special characters
*/

/*
** Things I read
**
** https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios/
** https://cygwin.com/ml/cygwin/2004-04/msg01158.html
** https://www.daemon-systems.org/man/terminfo.5.html
** https://en.wikibooks.org/wiki/Serial_Programming/termios
*/

static void	ft_select_usage_message(void)
{
	ft_dprintf(2, "How to use:\n\t./ft_select [-r {real}] arg1 [arg2...]\n");
	exit(EXIT_FAILURE);
}

void		ft_exit_err(char *str, int exit_code)
{
	ft_dprintf(2, "%s\n", str);
	exit(exit_code);
}

/*
** init signal
*/

void		ft_select_signal_handle(void)
{
	signal(SIGWINCH, ft_select_signal_handler);
	signal(SIGABRT, ft_select_signal_handler);
	signal(SIGQUIT, ft_select_signal_handler);
	signal(SIGTSTP, ft_select_signal_handler);
	signal(SIGCONT, ft_select_signal_handler);
	signal(SIGINT, ft_select_signal_handler);
}

/*
** runs wraper for tgetent
** makes a copy of the current calling programs tty
** and a duplicate for us to work with
** toggles cannonical mode of , min read chars = 1 , timeout disabled
**
** `ti'
** `vi'
**		String of commands to make the cursor invisible.
*/

void		set_custom_config(void)
{
	init_termcap(g_select.environ);
	tcgetattr(2, &g_select.old_attr);
	tcgetattr(2, &g_select.attr);
	g_select.attr.c_lflag &= ~(ICANON | ECHO);
	g_select.attr.c_cc[VMIN] = 1;
	g_select.attr.c_cc[VTIME] = 0;
	tcsetattr(2, TCSANOW, &g_select.attr);
	tputs(tgetstr("ti", NULL), 1, ft_select_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_select_putchar);
}

int			main(int ac, char **argv, char **environ)
{
	if (ac < 2 || (ac == 2 && argv[1][0] == '-'))
		ft_select_usage_message();
	g_select.environ = environ;
	set_custom_config();
	ft_select_signal_handle();
	ft_select_init_args(argv);
	g_select.ac = ac - 1;
	ft_select_handle_key_press();
	while (1)
		;
	return (0);
}
