/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:36:03 by sebferna          #+#    #+#             */
/*   Updated: 2024/06/25 11:36:03 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == 0)
		str = "(null)";
	while (str[i] != '\0')
	{
		ft_printchar(str[i], fd);
		i++;
	}
	return (i);
}
