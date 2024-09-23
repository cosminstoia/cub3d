/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:22:19 by cstoia            #+#    #+#             */
/*   Updated: 2024/03/13 16:00:05 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*destination;
	const char	*source;

	source = src;
	destination = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		*destination = *source;
		destination++;
		source++;
	}
	return (dst);
}
