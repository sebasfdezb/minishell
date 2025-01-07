/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:50:06 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/11 11:06:45 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
/* int	main(void)
{
	char	a[10] = "World";
	char	b[10] = "Hello";
	int		size;

	size = 10;
	printf("%zu" "%s\n", ft_strlcpy(b, a, size), b);
	printf("%lu" "%s", strlcpy(b, a, size), b);
	return (0);
} */