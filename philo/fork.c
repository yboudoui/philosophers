/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:34:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/17 08:22:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

t_fork	create_fork(void)
{
	t_fork	out;

	out = ft_calloc(1, sizeof(struct s_fork));
	if (out == NULL)
		return (NULL);
	pthread_mutex_init(&out->mutex, NULL);
	return (out);
}

void	destroy_fork(void *data)
{
	t_fork	input;

	input = data;
	if (input == NULL)
		return ;
	pthread_mutex_destroy(&input->mutex);
	free(input);
}

/* ************************************************************************** */

t_fork_array	create_fork_array(size_t size)
{
	size_t			index;
	t_fork_array	out;

	if (size == 0)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_fork_array));
	if (out == NULL)
		return (NULL);
	out->array = ft_calloc(size, sizeof(t_fork));
	if (out->array == NULL)
		return (destroy_fork_array(out), NULL);
	index = 0;
	while (index < size)
	{
		out->array[index] = create_fork();
		if (out->array[index] == NULL)
			return (destroy_fork_array(out), NULL);
		index += 1;
	}
	out->size = size;
	return (out);
}

void	destroy_fork_array(void *data)
{
	size_t			index;
	t_fork_array	input;

	input = data;
	if (input == NULL)
		return ;
	index = 0;
	while (index < input->size)
	{
		destroy_fork(input->array[index]);
		index += 1;
	}
	free(input->array);
	free(input);
}
