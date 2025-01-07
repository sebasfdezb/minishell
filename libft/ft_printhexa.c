/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:37:07 by sebferna          #+#    #+#             */
/*   Updated: 2024/06/25 11:37:07 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa(unsigned long long n, char c, int fd)
{
	unsigned long long	count;

	count = 0;
	if (n >= 16)
		count += ft_printhexa(n / 16, c, fd);
	if (c == 'x')
		ft_printchar("0123456789abcdef" [n % 16], fd);
	if (c == 'X')
		ft_printchar("0123456789ABCDEF" [n % 16], fd);
	count++;
	return (count);
}
