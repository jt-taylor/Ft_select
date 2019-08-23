/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_init_argument_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:16:36 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/22 10:23:10 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//insert arg
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
		g_select.arg_list->next = new;
		g_select.arg_list = new;
		return ;
	}
	else
	{
		new->prev = new;
		new->next = new;
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
}
