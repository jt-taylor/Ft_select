/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_init_termcaps.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:47:20 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/16 11:25:56 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_select.h"

void		init_termcap(char **env)
{
	(void)env;
	char	termbuffer[2048];
	char	*term_type;
	int		status;

	ft_bzero(termbuffer, 2048);
	term_type = getenv("TERM");
	if (term_type == 0)
		ft_exit_err("ERROR : env var TERM has no value", GEN_TERM_ERR);
	status = tgetent(termbuffer, term_type);
	if (status < 0)
		ft_exit_err("Could not access Termcap database\n", GEN_TERM_ERR);
	if (status == 0)
		ft_exit_err("Terminal type is not defined\n", GEN_TERM_ERR);
	//testing
	//printf("wow you did it , here's some stuff: TERM:%s , status=%d", term_type, status);
}
