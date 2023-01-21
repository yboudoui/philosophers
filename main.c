/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:27:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 17:58:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

int	main(int ac, char *av[])
{
	t_input	out;
	int		nb_arg;

	nb_arg = parse_arg(ac, av, &out);
	if (!nb_arg)
		return (-1);
	pool(out, routine);
	return (0);
}
