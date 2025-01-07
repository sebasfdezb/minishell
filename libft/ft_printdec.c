/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:37:47 by sebferna          #+#    #+#             */
/*   Updated: 2024/06/25 11:37:47 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printdec(long long int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += ft_printchar('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		count += ft_printdec(n / 10, fd);
	}
	c = n % 10 + '0';
	count += ft_printchar(c, fd);
	return (count);
}
