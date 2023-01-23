/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:27:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/23 12:32:47 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *ptr)
{
	if (ptr == NULL)
		return (NULL);
	wait_start(ptr);
	while (is_thinking(ptr)
//		&& take_fork(ptr)
		&& is_eating(ptr)
		&& is_sleeping(ptr)
	)
		continue ;
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_input	out;

	if (parse_arg(ac, av, &out))
		pool(out, routine);
	return (0);
}
