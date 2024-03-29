/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_assorted_func.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:15:58 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 12:33:24 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** this just putchar ,to stderr, but as an int as tputs wants int (*putc)(int),
** tputs is defined as
** int tputs(const char *str, int affcnt, int (*putc)(int));
** and my ft_putchar is void()
*/

int		ft_select_putchar(int c)
{
	return (write(2, &c, 1));
}

int		get_term_size(int return_width_or_height)
{
	struct winsize	win;

	ioctl(2, TIOCGWINSZ, &win);
	return ((return_width_or_height) ? win.ws_col : win.ws_row);
}

int		ft_select_count_columns(void)
{
	int		col;

	col = get_term_size(1);
	if (!col)
		col = 1;
	return (col);
}
