/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:00:18 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/15 16:59:50 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	calc_digit(unsigned long num, int *count, int base)
{
	if (num == 0)
	{
		(*count)++;
		return ;
	}
	while (num != 0)
	{
		num /= base;
		(*count)++;
	}
	return ;
}

int	put_num(unsigned long long num, int digit, int base, char index)
{
	char	c;

	digit--;
	while (digit > 0)
	{
		num /= base;
		digit--;
	}
	if (num % base < 10)
	{
		c = num % base + '0';
		if (write(1, &c, 1) == -1)
			return (-1);
	}
	else
	{
		if (index == 'u')
			c = num % base - 10 + 'A';
		else if (index == 'l')
			c = num % base - 10 + 'a';
		if (write(1, &c, 1) == -1)
			return (-1);
	}
	return (0);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
