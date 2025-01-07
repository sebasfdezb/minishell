/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:36:20 by sebferna          #+#    #+#             */
/*   Updated: 2024/06/25 11:36:20 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunsigned(unsigned long long int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n > 9)
		count += ft_printdec(n / 10, fd);
	c = n % 10 + '0';
	count += ft_printchar(c, fd);
	return (count);
}
