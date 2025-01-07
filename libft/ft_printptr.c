/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:36:36 by sebferna          #+#    #+#             */
/*   Updated: 2024/06/25 11:36:36 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(unsigned long long ptr, int fd)
{
	int	count;

	count = 0;
	count += ft_printstr("0x", fd);
	count += ft_printhexa(ptr, 'x', fd);
	return (count);
}
