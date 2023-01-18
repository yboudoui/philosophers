/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 00:49:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/06 15:22:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d || !s)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*memory_dup(void *src, size_t n)
{
	void	*output;

	output = ft_calloc(1, n);
	if (output)
		ft_memcpy(output, src, n);
	return (output);
}
