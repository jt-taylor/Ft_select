/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_handle_key_press.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:02:06 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/25 14:39:07 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** if input returns the row value
** else returns col value
**
** the winsize struct defined in sys/ioctl.h
** struct winsize
r* {
**   unsigned short ws_row;	/ rows, in characters /
**   unsigned short ws_col;	/ columns, in characters /
**   unsigned short ws_xpixel;	/ horizontal size, pixels /
**   unsigned short ws_ypixel;	/ vertical size, pixels /
** };
*/
static int	get_term_size(int return_width_or_height)
{
	struct winsize	win;

	ioctl(2, TIOCGWINSZ, &win);
	return ((return_width_or_height) ? win.ws_col : win.ws_row);
}

void			ft_select_put_arg(t_arg *arg_node, char *str)
{
	if (arg_node->selected)
		ft_putstr_fd("\033[7m", 2);
	if (arg_node == g_select.current_cursor)
		ft_putstr_fd("\033[4m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
}

static void		ft_select_display_args_elem(t_arg *arg_list, int row, int col)
{
	int		i;
	int		j;
	int		str_len;
	(void)str_len;

	i = -1;
	//this is hacky but  after it goes through once it's at the end of the
	// linked list and only puts the last argument
	// better solution add a pointer to the head or end node and 
	// check against that
	while (arg_list->prev != arg_list)
		arg_list = arg_list->prev;
	//for each row print an argument
	while (++i < row && arg_list != arg_list->next)
	{
		j = -1;
		//ft_dprintf(2, "\nrow = %d\ntrow = %d\n", row, get_term_size(0));
		if (ft_strlen(arg_list->arg_name) > (unsigned long)col)
		{
			write(2, "...\n", 3);
			arg_list = arg_list->next;
			continue ;
		}
		while (j < col)
		{
			// add a var to the struct to display which one is has the cursor on it
			//display underlined for selected args
			//print arg name;
			//if (arg_list == g_select.current_cursor)
			//	ft_putstr_fd("\033[334m", 2);
			//ft_putstr_fd("\033[7m", 2);
			//ft_putstr_fd(arg_list->arg_name, 2);
			//ft_putstr_fd("\033[0m", 2);
			j += ft_strlen(arg_list->arg_name) + 1;
			if (j > col)
				//ft_putstr_fd("\n", 2);
				break ;
			ft_select_put_arg(arg_list, arg_list->arg_name);
			if (arg_list->next == arg_list)
				break ;
			arg_list = arg_list->next;
			ft_putchar_fd(' ', 2);
		}
		ft_putstr_fd("\n", 2);
	}
}

static int		ft_select_count_columns(void)
{
	int		col;
	col = get_term_size(1);//  / //count_max_arg_len();
	if (!col)
		col = 1;
//	if ((//count_max_rg_en() = 1) * arg_count < //get_term_size(1))
//		//col = g_select.ac;
	return (col);
}

static void		ft_select_display_args(void)
{
	int		col;
	int		rows;

	if (g_select.arg_list == NULL)// || //len of args > window size)
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_select_putchar);
	col = ft_select_count_columns();
	//change this to ac / # col
	rows = get_term_size(0);
	//display
	ft_select_display_args_elem(g_select.arg_list, rows, col);
}

void		ft_select_handle_key_press(void)
{
	char	c[11];

	//infi loop until it reads a input charector
	while (1)
	{
		//display
		ft_select_display_args();
		ft_bzero(c, 11);
		read(2, c, 11);
		// if else chain to check what key was pressed 
		//handle space key
		if (ft_strequ(c, " "))
			ft_select_handle_space();
		//handle left arrow
//		if (c == '\e[D')
//			ft_select_handle_left_arrow();
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
			// exit ??
			exit(0);
		}
		// if not a key that we handle then keep runnnig the loop
	}
}
