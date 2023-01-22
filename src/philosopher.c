/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:51:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/22 19:56:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philosopher	create_philosopher(uint64_t id, t_pool_data pool)
{
	t_philosopher	out;

	if (pool == NULL)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_philosopher));
	if (out == NULL)
		return (NULL);
	out->data.id = id;
	out->data.pool = pool;
	out->data.fork[(id % 2)] = id;
	out->data.fork[!(id % 2)] = (id + 1) % pool->size;
	return (out);
}

void	destroy_philosopher(void *data)
{
	t_philosopher	input;

	input = data;
	if (input == NULL)
		return ;
	free(input);
}

/* ************************************************************************** */

t_philosopher_array	create_philosopher_array(size_t size, t_pool_data pool)
{
	size_t				index;
	t_philosopher_array	out;

	out = ft_calloc(1, sizeof(struct s_philosopher_array));
	if (out == NULL)
		return (NULL);
	out->array = ft_calloc(size, sizeof(t_philosopher));
	if (out->array == NULL)
		return (destroy_philosopher_array(out), NULL);
	index = 0;
	while (index < size)
	{
		out->array[index] = create_philosopher(index, pool);
		if (out->array[index] == NULL)
			return (destroy_philosopher_array(out), NULL);
		index += 1;
	}
	out->size = size;
	return (out);
}

void	destroy_philosopher_array(void *data)
{
	size_t				index;
	t_philosopher_array	input;

	input = data;
	if (input == NULL)
		return ;
	index = 0;
	while (index < input->size)
	{
		destroy_philosopher(input->array[index]);
		index += 1;
	}
	free(input->array);
	free(input);
}
