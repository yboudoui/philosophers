/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:47:03 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 17:47:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_arg(int ac, char *av[], t_input *out)
{
	union u_cast {
		t_input	data;
		int		raw[5];
	}	cast;
	int	index;

	ac -= 1;
	av += 1;
	if (ac < 4 || ac > 5)
		return (0);
	index = 0;
	while (index < ac)
	{
		cast.raw[index] = 0;
		if (!ft_atoi_to(&av[index], &cast.raw[index]))
			return (0);
		index += 1;
	}
//	cast.data.time_to_die *= 1000;
	cast.data.time_to_eat *= 1000;
	cast.data.time_to_sleep *= 1000;
	return ((*out) = cast.data, index);
}
