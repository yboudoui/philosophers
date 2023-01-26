/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:47:03 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/26 19:19:29 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
# include <stdio.h>
typedef union u_cast {
	t_input		data;
	uint64_t	raw[5];
}	t_cast;

int	parse_arg(int ac, char *av[], t_input *out)
{
	t_cast	cast;
	int		value;
	int		index;

	if (ac < 4 || ac > 5)
		return (0);
	index = 0;
	while (index < 5)
		cast.raw[index++] = 0;
	index = 0;
	while (index < ac)
	{
		cast.raw[index] = 0;
		if (!ft_atoi_to(&av[index], &value))
			return (0);
		cast.raw[index] = value;
		index += 1;
	}
	cast.data.eat = (ac == 5);
	cast.data.time_to_think = 0;
	if (cast.raw[1] > (cast.raw[2] + cast.raw[3]) * 2)
	{
		cast.data.time_to_think = cast.raw[1];
		cast.data.time_to_think -= ((cast.raw[2] + cast.raw[3]) * 2);
	}
	printf("%lu\n", cast.data.time_to_think);
	return ((*out) = cast.data, index);
}
