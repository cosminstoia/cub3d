/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:11:39 by cstoia            #+#    #+#             */
/*   Updated: 2024/04/17 17:30:32 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_gnl_strchr(char *str, int c)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		count;

	str = (char *)malloc((ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	count = 0;
	while (*s1)
		str[count++] = *s1++;
	while (*s2)
		str[count++] = *s2++;
	str[count] = '\0';
	return (str);
}

char	*ft_strjoin_and_free(char *string, char *buffer)
{
	char	*str;

	if (string == NULL || buffer == NULL)
		return (NULL);
	str = ft_gnl_strjoin(string, buffer);
	free(string);
	return (str);
}

void	ft_gnl_bzero(void *s, size_t n)
{
	unsigned char	*a;

	a = s;
	while (n > 0)
	{
		*a = 0;
		a++;
		n--;
	}
}
