/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:04:47 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:08:56 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*output;
	size_t	n;

	n = size * nmemb;
	if (!n)
		return (malloc(0));
	if ((n / size) != nmemb)
		return (NULL);
	output = malloc(n);
	while (output && n--)
		output[n] = 0;
	return (output);
}
