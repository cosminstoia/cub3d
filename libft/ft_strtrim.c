/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:05:43 by cstoia            #+#    #+#             */
/*   Updated: 2024/03/13 12:25:24 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!*set)
		return (ft_strdup(s1));
	if (!*s1)
		return (ft_strdup(""));
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL
		&& end >= start)
	{
		start++;
	}
	while (end > 0 && ft_strchr(set, s1[end]) != NULL && end >= start)
	{
		end--;
	}
	result = (char *)malloc((end - start + 2) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 2);
	return (result);
}
