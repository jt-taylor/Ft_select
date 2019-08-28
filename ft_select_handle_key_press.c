/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_handle_key_press.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:02:06 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 13:15:42 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** if input returns the row value
** else returns col value
**
** the winsize struct defined in sys/ioctl.h
** struct winsize
** {
**   unsigned short ws_row;	/ rows, in characters /
**   unsigned short ws_col;	/ columns, in characters /
**   unsigned short ws_xpixel;	/ horizontal size, pixels /
**   unsigned short ws_ypixel;	/ vertical size, pixels /
** };
*/

void				ft_select_put_arg(t_arg *arg_node, char *str)
{
	if (arg_node->selected)
		ft_putstr_fd("\033[7m", 2);
	if (arg_node == g_select.current_cursor)
		ft_putstr_fd("\033[4m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
}

static inline t_arg	*ft_select_display_args_elem_inner(int j, int col,
		t_arg *arg_list)
{
	while (j < col)
	{
		j += ft_strlen(arg_list->arg_name) + 1;
		if (j > col)
			break ;
		ft_select_put_arg(arg_list, arg_list->arg_name);
		if (arg_list->next == arg_list)
			break ;
		arg_list = arg_list->next;
		ft_putchar_fd(' ', 2);
	}
	ft_putstr_fd("\n", 2);
	return (arg_list);
}

static void			ft_select_display_args_elem(t_arg *arg_list,
		int row, int col)
{
	int		i;
	int		j;
	int		last;

	i = -1;
	while (arg_list->prev != arg_list)
		arg_list = arg_list->prev;
	while (++i < row && (arg_list != arg_list->next || last))
	{
		j = -1;
		if (ft_strlen(arg_list->arg_name) >= (unsigned long)col)
		{
			ft_select_put_arg(arg_list, "...\n");
			arg_list = arg_list->next;
			last = 1;
			continue ;
		}
		arg_list = ft_select_display_args_elem_inner(j, col, arg_list);
		last = 0;
	}
}

void				ft_select_display_args(void)
{
	int		col;
	int		rows;

	if (g_select.arg_list == NULL)
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_select_putchar);
	col = ft_select_count_columns();
	rows = get_term_size(0);
	ft_select_display_args_elem(g_select.arg_list, rows, col);
}

void				ft_select_handle_key_press(void)
{
	char	c[11];

	while (1)
	{
		ft_select_display_args();
		ft_bzero(c, 11);
		read(2, c, 11);
		if (ft_strequ(c, " "))
			ft_select_handle_space();
		else if (ft_strequ(c, "\e[D"))
			ft_select_handle_left_arrow();
		else if (ft_strequ(c, "\e[C"))
			ft_select_handle_right_arrow();
		else if (ft_strequ(c, "\x7f"))
			ft_select_remove_arg();
		else if (ft_strequ(c, "\e"))
			handle_signal_exit();
		else if (ft_strequ(c, "\n"))
		{
			ft_select_reset_default_term_config();
			ft_select_handle_enter_key();
			exit(0);
		}
	}
}
