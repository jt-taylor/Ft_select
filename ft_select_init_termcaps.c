/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_init_termcaps.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:47:20 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/28 12:13:02 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		init_termcap(char **env)
{
	char	*termbuffer;
	char	*term_type;
	int		status;

	(void)env;
	termbuffer = g_select.termbuffer;
	ft_bzero(termbuffer, 2048);
	term_type = getenv("TERM");
	if (term_type == 0)
		ft_exit_err("ERROR : env var TERM has no value", GEN_TERM_ERR);
	status = tgetent(termbuffer, term_type);
	if (status < 0)
		ft_exit_err("Could not access Termcap database\n", GEN_TERM_ERR);
	if (status == 0)
		ft_exit_err("Terminal type is not defined\n", GEN_TERM_ERR);
	g_select.term_name = term_type;
	if (!isatty(2))
	{
		ft_dprintf(2, "fd: 2 does not belong to a tty\n");
		exit(1);
	}
}
