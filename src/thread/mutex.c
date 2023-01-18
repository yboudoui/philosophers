/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 06:51:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/17 07:53:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

t_mutex	create_mutex(void *data)
{
	t_mutex	out;

	out = ft_calloc(1, sizeof(struct s_mutex));
	if (out == NULL)
		return (NULL);
	pthread_mutex_init(&out->lock, NULL);
	out->data = data;
	return (out);
}

void	destroy_mutex(void *data)
{
	t_mutex	input;

	input = data;
	if (input == NULL)
		return ;
	pthread_mutex_destroy(&input->lock);
	free(input);
}
