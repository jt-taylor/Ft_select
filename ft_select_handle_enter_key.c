/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_handle_enter_key.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:16:13 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/24 11:36:01 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_select_handle_enter_key(void)
{
	t_arg	*tmp;
	int		count;

	count = 0;
	tmp = g_select.arg_list;
	while (tmp->prev != tmp)
		tmp = tmp->prev;
	while (tmp->next != tmp)
	{
		if (tmp->selected)
		{
			if (count)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(tmp->arg_name, 1);
			count = 1;
		}
		tmp = tmp->next;
	}
	if (tmp->selected)
	{
		if (count)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(tmp->arg_name, 1);
	}
}
