/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:00:21 by cstoia            #+#    #+#             */
/*   Updated: 2024/03/13 16:30:57 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	total_len;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	total_len = dstlen + srclen;
	i = 0;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while (src[i] != '\0' && dstlen + 1 < dstsize)
	{
		dst[dstlen] = src[i];
		dstlen++;
		i++;
	}
	dst[dstlen] = '\0';
	return (total_len);
}
