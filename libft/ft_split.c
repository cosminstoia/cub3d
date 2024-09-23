/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 08:38:55 by cstoia            #+#    #+#             */
/*   Updated: 2024/03/14 19:11:34 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			return (count);
		while (*str != '\0' && *str != c)
			str++;
		count++;
	}
	return (count);
}

static size_t	count_chars(const char *s, char delimiter)
{
	size_t	count;

	count = 0;
	while (*s != '\0' && *s != delimiter)
	{
		count++;
		s++;
	}
	return (count);
}

static char	**free_array(char **result, int i)
{
	while (i)
		free(result[--i]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;

	i = 0;
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || result == NULL)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		result[i] = ft_substr(s, 0, count_chars(s, c));
		if (!result[i])
			return (free_array(result, i));
		s += count_chars(s, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}
