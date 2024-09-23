/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:39:40 by cstoia            #+#    #+#             */
/*   Updated: 2024/03/13 20:09:31 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	fill_result(char **result, int n, int mem_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (n < 0)
	{
		(*result)[0] = '-';
		n = -n;
		j++;
	}
	i = mem_size - 1;
	while (i >= j)
	{
		(*result)[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		mem_size;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	mem_size = count_digits(n);
	if (n < 0)
		mem_size++;
	result = (char *)malloc((mem_size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	fill_result(&result, n, mem_size);
	result[mem_size] = '\0';
	return (result);
}
