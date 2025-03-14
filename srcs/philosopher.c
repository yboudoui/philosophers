/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:51:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 13:54:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philosopher	create_philosopher(uint64_t id, void *shared_data)
{
	t_philosopher	out;

	if (shared_data == NULL)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_philosopher));
	if (out == NULL)
		return (NULL);
	out->data.id = id;
	out->data.shared_data = shared_data;
	out->data.last_eat = time_now_millisecond();
	pthread_mutex_init(&out->data.mutex, NULL);
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

t_philosopher_array	create_philosopher_array(size_t size, void *shared_data)
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
		out->array[index] = create_philosopher(index, shared_data);
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
