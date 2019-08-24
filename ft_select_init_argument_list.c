/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_init_argument_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:16:36 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/23 21:33:32 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** removes the current arg and sets g_select_current_currsor to the next arg
*/
void		ft_select_remove_arg()
{
	t_arg	*tmp;

	tmp = g_select.current_cursor;
	if (tmp->next != tmp)
		g_select.current_cursor = tmp->next;
	else if (tmp->prev != tmp)
		g_select.current_cursor = tmp->prev;
	else
		handle_signal_exit();
	//if first
	if (tmp->prev == tmp)
	{
		tmp->next->prev = tmp->next;
		free(tmp->arg_name);
		free(tmp);
	}
	//if last
	else if (tmp->next == tmp)
	{
		tmp->prev->next = tmp->prev;
		free(tmp->arg_name);
		free(tmp);
	}
	//if middle
	else
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		free(tmp->arg_name);
		free(tmp);
	}
}

static void	ft_select_insert_arg(char *str)
{
	t_arg	*new;

	new = (t_arg*)malloc(sizeof(t_arg));
	new->arg_name = ft_strdup(str);
	new->selected = 0;
	g_select.total_count++;
	//if first
	if (g_select.arg_list)
	{
		new->prev = g_select.arg_list;
		new->next = new;
		new->head = g_select.arg_list->head;
		g_select.arg_list->next = new;
		g_select.arg_list = new;
		return ;
	}
	else
	{
		new->prev = new;
		new->next = new;
		new->head = new;
		g_select.arg_list = new;
	}
}

void		ft_select_init_args(char **arg)
{
	int	i;

	i = 0;
	g_select.total_selected = 0;
	g_select.total_count = 0;
	while (arg[++i])
	{
		ft_select_insert_arg(arg[i]);
		//add arg[i] to a linked list that will store the arg_name , and 
		//if it is selected or not
			//and forward // backward pointers
	}
	g_select.current_cursor = g_select.arg_list->head;
}
