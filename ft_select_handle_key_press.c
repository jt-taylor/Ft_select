/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_handle_key_press.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:02:06 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/22 16:04:21 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_select_display_args_elem(t_arg *arg_list, int row, int col)
{
	int		i;
	int		j;
	int		str_len;
	(void)str_len;

	i = -1;
	//for each row print an argument
	while (++i < row)
	{
		j = -1;
		while (++j < col)
		{
			// add a var to the struct to display which one is has the cursor on it
			//display underlined for selected args
			//print arg name;
			ft_putstr_fd(arg_list->arg_name, 2);
			if (arg_list->next == arg_list)
				break ;
			arg_list = arg_list->next;
		}
		ft_putstr_fd("\n", 2);
	}
}

static void		ft_select_count_columns(void)
{
	int		col;
	col = //get_term_size(1) / //count_max_arg_len();
	if (!col)
		col = 1;
	if ((//count_max_rg_en() = 1) * arg_count < //get_term_size(1))
		//col = g_select.ac;
	return (col);
}

static void		ft_select_display_args(void)
{
	int		columns;
	int		rows;

	if (g_select.arg_list == NULL || //len of args > window size)
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_select_putchar);
	columns = //count columns;
	rows = //count rows;
	if (rows > //window size)
		return ;
	//display
	ft_select_display_args_elem(g_select.arg_list, rows, columns);
}

void		ft_select_handle_key_press(void)
{
	long c;

	//infi loop until it reads a input charector
	while (1);
	{
		//display
		c = 0;
		read(2, &c, 8);
		// if else chain to check what key was pressed 
		// if not a key that we handle then keep runnnig the loop
	}
}
