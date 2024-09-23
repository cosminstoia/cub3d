/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:58:40 by cstoia            #+#    #+#             */
/*   Updated: 2024/03/13 16:30:46 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	size_t	len;
	char	*dup;

	i = 0;
	len = ft_strlen(s1);
	if (s1 == NULL)
	{
		return (NULL);
	}
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup != NULL)
	{
		while (s1[i])
		{
			dup[i] = s1[i];
			i++;
		}
		dup[i] = '\0';
	}
	return (dup);
}
