/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_init_argument_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:16:36 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 12:34:12 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** removes the current arg and sets g_select_current_currsor to the next arg
*/

static inline void	ft_select_norm_limit(t_arg *tmp)
{
	if (tmp->prev == tmp)
	{
		tmp->next->prev = tmp->next;
		free(tmp->arg_name);
		free(tmp);
	}
	else if (tmp->next == tmp)
	{
		tmp->prev->next = tmp->prev;
		free(tmp->arg_name);
		free(tmp);
	}
	else
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		free(tmp->arg_name);
		free(tmp);
	}
}

void				ft_select_remove_arg(void)
{
	t_arg	*tmp;

	tmp = g_select.current_cursor;
	if (tmp->next != tmp)
		g_select.current_cursor = tmp->next;
	else if (tmp->prev != tmp)
		g_select.current_cursor = tmp->prev;
	else
		handle_signal_exit();
	ft_select_norm_limit(tmp);
}

static void			ft_select_insert_arg(char *str)
{
	t_arg	*new;

	new = (t_arg*)malloc(sizeof(t_arg));
	new->arg_name = ft_strdup(str);
	new->selected = 0;
	g_select.total_count++;
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

void				ft_select_init_args(char **arg)
{
	int	i;

	i = 0;
	g_select.total_selected = 0;
	g_select.total_count = 0;
	while (arg[++i])
	{
		ft_select_insert_arg(arg[i]);
	}
	g_select.current_cursor = g_select.arg_list->head;
}
