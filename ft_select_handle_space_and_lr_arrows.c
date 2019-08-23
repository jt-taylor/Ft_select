/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_handle_space_and_lr_arrows.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:24:34 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/23 16:50:00 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** this is pretty simple , it just swaps between zero and 1
** the int is checked when writing the argument
** doing it this way is pretty simple because we clear the screen 
** then right the arguments again and just go back and forth for that
*/

void	ft_select_handle_space(void)
{
	g_select.current_cursor->selected = (g_select.current_cursor->selected ^ 1);
}

void	ft_select_handle_left_arrow(void)
{
	t_arg	*tmp;

	if (g_select.current_cursor->prev != g_select.current_cursor)
		g_select.current_cursor = g_select.current_cursor->prev;
	else
	{
		tmp = g_select.current_cursor;
		while (tmp->next != tmp)
			tmp = tmp->next;
		g_select.current_cursor = tmp;
	}
}

void	ft_select_handle_right_arrow(void)
{
	t_arg	*tmp;

	if (g_select.current_cursor->next != g_select.current_cursor)
		g_select.current_cursor = g_select.current_cursor->next;
	else
	{
		tmp = g_select.current_cursor;
		while (tmp->prev != tmp)
			tmp = tmp->prev;
		g_select.current_cursor = tmp;
	}
}

void	ft_select_handle_del_key();
{
	//if last arg exit the program
}
